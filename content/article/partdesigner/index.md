---
title: Lego Part Designer
date: 2019-05-01
tags:
  - cad
  - webdev
  - opengl
  - webgl
  - 3dprinting

---

{{< img "partdesigner.png" "" >}}

I made a web app that lets you design your own Lego Technic parts and save them as printable STL files.
You can check it out [here](https://marian42.de/partdesigner/).

<!--more-->

I got the idea for this project when I was building with Lego parts and wondered how many of the common parts can be described with a simple rule set.
The system I came up with assembles the parts out of five basic blocks:
Pin Hole, Axle Hole, Pin, Axle and Solid.

{{< img "blocks.png" "" >}}

Internally, each block consists of four *small blocks*.
By default, double sized blocks are created that consist of eight small blocks.
All blocks are placed using coordinates of the small blocks so that they can be placed at "half" positions.

To accomodate 0.2 mm margins at the outside faces of the part, the small blocks are split further into three *tiny blocks* per dimension.
The two outer tiny blocks have the size of the margin and the center tiny block takes the remaining space.
Note that a tiny block can be in the center on one axis and in the margin on another.
The code has some logic to determine which tiny blocks are part of the model and which aren't.
Finally, before rendering the tiny blocks, they are merged to lower the number of polygons.

{{< img "tinyblocks.png" "" >}}

The app is written in TypeScript and uses WebGL to render the model.
The difficult part is generating the mesh for the model.
This is done directly in the TypeScript code, *without* using a [CSG](https://en.wikipedia.org/wiki/Constructive_solid_geometry) library.
There are no big surprises in the implementation, just lots and lots of corner cases to handle, many of them literal corner cases.
The source code for this project is available on [Github](https://github.com/marian42/partdesigner).

One problem with TypeScript is its lack of support for [operator overloading](https://github.com/Microsoft/TypeScript/issues/6936).
This project uses lots of vector operations and without operator overloading, I can't write `v1 = v2 + v3 * f;`, instead I have to write `v1 = v2.plus(v3.times(f));`.
This can make the code unnecessarily cluttered.

The app features a catalog that shows a selection of existing Lego parts that can be made with this system.
Of course the point of this tool is to make parts that don't already exist, but this can give you some inspiration.

{{< img "catalog.png" "" >}}

The preview images for the catalog are not stored on the server.
Instead, they are rendered using the same code that renders the model in the editor.

# Orrery gear box

To demonstrate the practical use of this app, I made a gear box for a Lego orrery.
The orrery is based on [a design from JK Brickworks](https://jkbrickworks.com/earth-moon-and-sun-orrery/).
I took the sun, earth and moon design from that model and designed everything else myself.

Here is the [gear box in the part designer](https://marian42.de/partdesigner/?part=190x11f5x129by0313y039by0434y0192y0269x1380Z0426x15acZ068ex11edy073y097y0c4y0fby013dy02edx14e0x1787x118by01e6y0766x024fy02c7y0977x034fy03e8y0562x1730x195ax1be8y0493y0d47y03bcX263fx183ax1a95x1d7y2467y210ey2512y21f9y0262y0564y0ee4y0636y0107ay06b5Z07afz078ax19c0Z0b00x1167y1229y0327y0469Y05f7y01b5y1292y03afy0514Y06c9y0141y11fby02f1y1c5bx118fy1264y0379y157by164dy13ecy1566y0734y11254y0497y1638y0831y11425y0dd1x146by17dby0516y18d8y0b2ez0dd2z0f63x199ey1c34Z0da7Z0acay110ccY0147dy1568y1736y0960y01640y01aaey163ay1833y0a8cy01850y01d01y11112x15fby0a1by06cdy0b47y010e4y01297y0bf0y01ab0y0d4fy01d03y046fy25fdy07dfy0a1dy0cbfy2fcdy051ay26cfy08dcy0b49y0e1ey21163y05d8y0e05y01316y06aay0f7fY014e7y0791z18a0z19c7z11115z112e1z116d7x19a2y01499Y0acey01689Y0c13y01ae3y0d72y01d36y0eecy01facy01082y02246y01904x1125cy01646x11ab4x11faex1253cy0142dy02821y0186dx11d20x12263x1):

{{< img "orrerybase.png" "" >}}

After printing and adding gears, it looks like this:

{{< img "gears.jpg" "" >}}

{{< img "orrery1.jpg" "" >}}

And finally, here is the completed orrery:

{{< img "orrery2.jpg" "" >}}

The gears run reasonably smoothly in the printed part.
Choosing the size of the axle holes is a tradeoff between having too much resistance and being too loose.
Of course the real, injection molded parts have tighter tolerances than one can achieve with a consumer 3D printer.
This example shows that 3D printed parts can be combined with original Lego parts.
One advantage of printing parts like this is that it saves you the time to figure out how a structure can be made with existing Lego parts.
