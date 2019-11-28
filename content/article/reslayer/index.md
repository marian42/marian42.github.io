---
title: 'Work in progress: Location based online game'
date: 2015-09-12T23:10:12+00:00
tags:
  - gamedev
  - webdev
  - procgen

---

{{< img "Screenshot-21.png" "" >}}

This is a game prototype I’m currently working on. The game is played online, on a real world map and the location of the player is also the location ingame, just like in Ingress.
<!--more-->
I know that making an online game like this is an ambitious goal and it will probably never be finished, but this prototype is a good way for me to test the game mechanic and see what works and what doesn’t.

The prototype is a web app and doesn’t yet use the player’s location, meaning they can interact anywhere on the map. If all works out, I’ll make a mobile client, which will be the actual game.

The game is about finding resources and mining them. I’m trying to make the resource locations meaningful and related to the real world. So I wrote an engine that procedurally distributes resources on the map, based on map data provided by Open Street Map. This allows me to define rules like “Resource 1 can be found at water fountains near public parks”, or “Resource 2 can be found only in forests and only within 100 meters of a school” and so on. Here is an example:

{{< img "Screenshot-5.png" "" >}}

The green resources are distributed randomly across roads, the pink ones are around monuments, orange resources can be found near shops. The goal of this is to encourage players to think about what they can do at a certain place without looking at the map. Also, different strategies will emerge in rural and urban areas and some places will be strategically more important than others. This is a feature that Ingress lacks, the Ingress gameplay differs very little across different locations.

There are four kinds of buildings that can be placed anywhere on the map.

{{< img "Screenshot-22.png" "" >}}

In the actual game, players can only place buildings at their current location, and only if there isn’t another building already.

Buildings consume and output resources, which are transported via links. All buildings can be connected with links and the system will figure out the most effective way to use them.

{{< img "Screenshot-14.png" "" >}}

A mine picks up resources from the ground.

{{< img "Screenshot-15.png" "" >}}

A warehouse stores them.

{{< img "Screenshot-12.png" "" >}}

There are ten tiers of resources and only the resources of the first tier can be aquired by mining. Higher tier resources are made by directing two different kinds of resources of the same tier into a factory and it will output a resource of a higher tier. This encourages players to build complex networks of mines, factories and warehouses, like this one:

{{< img "Screenshot-20.png" "" >}}

And finally, a tower protects someones buildings. Buildings that are not in the range of a tower can be used by everyone. So you need to build a tower to keep people from pulling resources out of your factories and looting your warehouses. High-tier resources serve as explosives to take down other’s towers and use their production networks.

{{< img "Screenshot-8.png" "" >}}

You can see that two of the mines are idle, because the warehouse has a limited input rate.

The goal of this mechanic is to encourage teamwork, reward efforts and provide some permanence to the players’ actions, as opposed to Ingress. In Ingress, it doesn’t really matter which portals of which place you conquer, since someone else will have taken them over by the next day. I’m trying to make a game that fixes some of the problems that Ingress has.

The screenshots in this article contain map data by [OpenStreetMap][1] (ODbL) and Dark Matter tiles by [CartoDB][2] ([CC BY 3.0][3]).

 [1]: https://openstreetmap.org
 [2]: https://cartodb.com/attributions#basemaps
 [3]: https://creativecommons.org/licenses/by/3.0/
