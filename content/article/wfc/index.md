---
title: Infinite procedurally generated city with the Wave Function Collapse algorithm
date: 2019-01-06
tags:
  - unity
  - procgen
  - modeling
  - graphics

---

{{< img "wfc.jpg" "" >}}

This is a game where you walk through an infinite city that is procedurally generated as you walk.
It is generated from a set of blocks with the Wave Function Collapse algorithm. <!--more-->

You can download a playable build of the game on [itch.io](https://marian42.itch.io/wfc) and you can get the [source code on github](https://github.com/marian42/wavefunctioncollapse).
Here is a video of me walking around a generated city:

{{< youtube -W7zt8181Zo >}}

# The algorithm

I will use the word "slot" for a place in the 3D voxel grid that can contain a block (or be empty) and I will use the word "module" for a block that can inhabit such a slot.

The algorithm chooses which modules to select for each slot in the world.
The array of slots is considerd a wave function in an unobserved state.
That means that each slot has a set of possible modules that could be put there.
In the language of quantum mechanics, one could say "The slot is in superposition of all modules".
The world starts in a completely unobserved state where every module is possible in any slot.
One by one, each slot is collapsed.
That means, one module from the set of possible modules is selected at random.
This is followed by a step of constraint propagation.
For each module, only a subset of modules are allowed to be placed adjacent to it.
Whenever a slot is collapsed, the sets of modules that are still possible to be placed in nearby slots need to be updated.
The constraint propagation step is the most computationally expensive part of the algorithm.

An important aspect of the algorithm is deciding which slot to collapse.
The algorithm always collapses the slot with the lowest [entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)).
That is the slot which has the least amount of choice (or chaos).
If all modules have the same probability, the slot with the smallest number of possible modules has the lowest entropy.
In general, modules have different probabilities to be selected.
A slot with two possible modules of the same probability has more choice (greater entropy) than one with two modules where one is very likely and one is very unlikely.

![](https://camo.githubusercontent.com/dc39c61e02aa67abd0f923628cf241120d14f517/687474703a2f2f692e696d6775722e636f6d2f734e75425653722e676966)  
(Gif by [ExUtumno on Github](https://github.com/mxgmn))

You can find more information and some beautiful examples of the [Wave Function Collapse algorithm here](https://github.com/mxgmn/WaveFunctionCollapse).
The algorithm was proposed to generate 2D textures from a single example.
In that case, the module probabilities and adjacency rules are determined based on how they occur in the example.
In my case, they are supplied manually.

Here is a video of the algorithm in action:

<video autoplay loop muted src="wfc.mp4">

# About blocks, prototypes and modules

The world is generated from a set of ~100 blocks, which I made with Blender.
I started out with a small number of blocks and made more whenever I had some spare time.

{{< img "blocks.png" "" >}}

The algorithm needs to know which modules can be placed next to each other.
Each module has 6 lists of possible neighbors, one for each direction.
But I wanted to avoid having to create this list manually.
I also wanted a way to automatically generate rotated variants of my blocks.

Both can be achieved by using what I call *module prototypes*.
This is a MonoBehaviour that can be conveniently edited in the Unity editor.
The modules together with lists of allowed neighbors and the rotated variants are created automatically from these.

A difficult problem was figuring out how to model adjacency information so that this automatic process works.
Here is what I came up with:

{{< img "blocks2.png" "" >}}

Each block has 6 connectors, one for each face.
The connector has a number.
In addition, horizontal connectors are either *flipped*, *not flipped* or *symmetric*.
Vertical connectors either have a rotation index between 0 and 3 (b, c, d in the screenshot) or they are flagged *rotationally invariant*.

Based on this, I can automatically check which modules are allowed next to each other.
Adjaced modules must have the same connector number.
And their symmetry must match (same rotation index vertically, a *flipped* and *not flipped* pair horizontally) or they must be symmetric / invariant.

{{< img "moduleprototype.png" "" >}}

There are exclusion rules that allow me to prohibit neighbors that would otherwise be allowed.
Some blocks with matching connectors just don't look nice next to each other.
Here is an example of a map generated *without* the exclusion rules:

{{< img "noexclusions.jpg" "" >}}

# Reaching infinity

The original Wave Function Collapse algorithm generates finite maps.
I wanted to have a world that expands further and further as you walk through it.

My first approach was to generate chunks of finite size and use the connectors of adjacent chunks as constraints.
If a chunk is generated and an adjacent chunk was already generated, only modules are allowed that fit with the existing modules.
The problem with this approach is, whenever a slot is collapsed, the constraint propagation will limit the posibilities even a few slots away.
In this image you can see all the places affected from collapsing just one slot:

{{< img "cloud.png" "" >}}

When just generating a single chunk at once, constraints were not propagated to adjacent chunks.
This led to modules being selected within the chunk that would not be allowed when considering the other chunks.
When the algorithm would then try to generate the next chunk, it could not find any solution.

Instead of using chunks, I store the map in a dictionary that maps a slot position to a slot.
It is only populated when needed.
Some parts of the algorithm needed to be adjusted to this.
When selecting a slot to collapse, not all infinite slots can be considered.
Instead, only a small area of the map is generated at once, when the player reaches it.
Constraints are still propagated outside of this area.

In some cases this approach doesn't work.
Consider a module set with the straight tunnel piece from the screenshot above, but no tunnel entrance.
If the algorithm selects such a tunnel module, this predetermines an infinite tunnel.
The constraint propagation step would try to allocate an infinite amount of slots.
I designed the module set to avoid this problem.

# Boundary constraints

There are two important boundary constraints:
Faces at the top of the map must have "air" connectors.
Faces at the bottom of the map must have "solid" connectors.
If these constraints are not met, there are holes in the ground and buildings with missing roofs.

In a finite map, this would be easy to do:
For all slots in the top and bottom layer, remove all modules with unwanted connectors.
Then use constraint propagation to remove other modules that are no longer valid.

In the infinite map, this doesn't work because there are infinitely many slots in the top and bottom layer.
Naively, I would only remove these modules in the top and bottom layer once the slots are created.
However, removing a module in one top layer slot implies constraints for its neighbor slots.
This leads to a cascading effect which would again allocate slots infinitely.

I solved this by creating a 1×n×1 map, where n is the height.
This map uses world wrapping to propagate constraints.
This works like Pacman, you leave the level on the right and enter on the left.
Now in this map I can apply all the boundary constraints.
Whenever a new slot in the infinite map is created, it is initialized with the module set of the corresponding position in that map.

# Error states and backtracking

Sometimes the WFC algorithm will reach a state where a slot has zero possible modules.
In applications with a finite world, you can just discard the result and start over.
In the infinite world, this doesn't work, since a part of the world has already been shown to the player.
I started with a solution where a white block would be spawned in places of errors.

My current solution is backtracking.
The order in which the slots where collapsed and some information about constraint propagation is stored as a history.
If the WFC algorithm fails, some of the history is undone.
This works in most cases, but sometimes errors are recognized very late which leads to many steps being backtracked.
In rare cases, the slot in which the player is, is regenerated.

In my opinion, this limitation makes the WFC approach for infinite worlds unsuitable for commercial games.

# Outlook

I started working on this when I saw a [talk by Oskar Stålberg who uses the WFC algorithm to generate levels in Bad North](https://www.youtube.com/watch?v=0bcZb-SsnrA).
Most of the basics were implemented during the [procjam](http://www.procjam.com/) week.

I have some ideas about future improvements, but I'm not sure if I'll ever add gameplay.
And if I do, it will probably not be the battle royale game that you are envisioning.
But if you want to see your favorite game mechanic added to this, just do it yourself!
The source code is available after all and it's MIT licensed.
