# minirt
This project is an introduction to the beautiful world of Raytracing.

### [`the first thing I search on youtube`](https://www.youtube.com/results?search_query=lectures+on+ray+tracing+from+ivy+college)

#### after that I looked into my old fdf to see if  I still remember anything about the mlx graphical library from 42:
After cloning the library from this repos:
```
git@github.com:42Paris/minilibx-linux.git
```
## Compilation and Dependencies 
I have to install the library needed on my ubuntu laptop
```
 sudo apt-get install libx11-dev;
 sudo apt-get install libxext-dev;
 sudo apt-get install libbsd-dev;
```
You would already know all this stuff if you read the [`docs`](https://harm-smits.github.io/42docs/libs/minilibx)

Also if you're into make great Makefile, check out this post about [`Universal Compilation`](https://reactive.so/post/42-a-comprehensive-guide-to-so_long).

This can be accomplished by checking [`uname`](https://stackoverflow.com/questions/24563150/makefile-with-os-dependent-compiler).


## UC davis Computer Graphics course
the main goal ofor me  is to learn quickly the basics of computer graphics needed to complete the [`minirt`](https://github.com/alessiotucci/minirt) project.
For this reason I will use the [`minilibx`](https://github.com/42Paris/minilibx-linux) as graphical library. 
those 2 video will help you get started with the minimal library.
* [video1](https://elearning.intra.42.fr/notions/minilibx/subnotions/mlx-introduction/videos/introduction-to-minilibx)
* [vide2](https://elearning.intra.42.fr/notions/minilibx/subnotions/mlx-events/videos/minilibx-events)
* [videoFDF](https://elearning.intra.42.fr/notions/fdf/subnotions/introduction-to-fdf/videos/introduction-to-fdf)
* [videoMINIRT](https://elearning.intra.42.fr/notions/rtv1-rt/subnotions/rtv1-rt-general-presentation-rtv1-rt/videos/presentation-generale-rtv1-et-rt)

#### Lectures
The lectures cover vast majority of all the knowledge you need for minirt, and even more. At almost halfway all the topics, including bonuses are already been introduced and discussed by the professor [Ken Joy](https://faculty.engineering.ucdavis.edu/joy/).
#### quick tip given by the professor:
using the filetype:pdf is helpful during google search
[this is my latest google search](https://www.google.com/search?q=pinhole+camera+raytracing+filetype%3Apdf&sca_esv=2e2146100c56afd5&sca_upv=1&rlz=1C1GCEU_enIT1098IT1098&sxsrf=ACQVn088X3H7JqTCqvSRRttbEIyVRH1ZDQ%3A1714481108012&ei=1OcwZpUin4n27w-lw7-oCw&ved=0ahUKEwiV3Krr--mFAxWfhP0HHaXhD7UQ4dUDCBA&uact=5&oq=pinhole+camera+raytracing+filetype%3Apdf&gs_lp=Egxnd3Mtd2l6LXNlcnAiJnBpbmhvbGUgY2FtZXJhIHJheXRyYWNpbmcgZmlsZXR5cGU6cGRmSKwwUKEHWIEvcAN4AJABAZgB9gGgAdcPqgEGMy4xMi4xuAEDyAEA-AEBmAIPoAKQDMICChAAGLADGNYEGEfCAggQABgWGAoYHsICCBAAGIAEGKIEwgIHECEYoAEYCpgDAIgGAZAGCJIHBDMuMTKgB7FB&sclient=gws-wiz-serp)
## UC-davis-graphics-course
<!---
[![video 1](https://ytcards.demolab.com/?id= " ")]() |
-->
[extra notes](https://www.cs.sjtu.edu.cn/~shengbin/course/vr/slides/VR_Lecture8_ShengBin.pdf)

| Lectures    | video | notes | 
|-------------|-------|--------| 
|1)           |  [![video 1](https://ytcards.demolab.com/?id=01YSK5gIEYQ "Introduction to Computer Graphics")](https://www.youtube.com/watch?v=01YSK5gIEYQ)     |  | 
|2) Curves in the Plane               |  [![video 2](https://ytcards.demolab.com/?id=0NbD-c0Ctdk " ")](https://www.youtube.com/watch?v=0NbD-c0Ctdk)| [CHAIKIN’S ALGORITHMS FOR CURVES](https://www.cs.unc.edu/~dm/UNC/COMP258/LECTURES/Chaikins-Algorithm.pdf)  [Bezier curve](https://it.wikipedia.org/wiki/Curva_di_B%C3%A9zier),  [](https://www.google.com/search?q=pascal+triangle&oq=pascal++triangle+&gs_lcrp=EgZjaHJvbWUyBggAEEUYOTIJCAEQABgTGIAEMgkIAhAAGBMYgAQyCQgDEAAYExiABDIJCAQQABgTGIAEMgkIBRAAGBMYgAQyCQgGEAAYExiABDIJCAcQABgTGIAEMgkICBAAGBMYgAQyCQgJEAAYExiABNIBCDY4NDZqMGo3qAIAsAIA&sourceid=chrome&ie=UTF-8) [bezier curve recursive formula](https://www.google.com/search?q=bezier+curve+recursive+formula&sca_esv=0498115c76c36171&sca_upv=1&sxsrf=ACQVn0_vwGipkNLZkpyjHrBcoqfpjwtDHQ%3A1714323311409&ei=b38uZuqgE7Tzi-gP25WLkAo&ved=0ahUKEwiqlIGAsOWFAxW0-QIHHdvKAqIQ4dUDCBA&uact=5&oq=bezier+curve+recursive+formula&gs_lp=Egxnd3Mtd2l6LXNlcnAiHmJlemllciBjdXJ2ZSByZWN1cnNpdmUgZm9ybXVsYTIIEAAYgAQYogQyCBAAGIAEGKIEMggQABiABBiiBDIIEAAYgAQYogRI-xBQ3gZYzQ5wAngAkAEAmAFuoAGzBKoBAzUuMbgBA8gBAPgBAZgCCKAC7ATCAgsQABiABBiwAxiiBJgDAIgGAZAGBZIHAzUuM6AHnxM&sclient=gws-wiz-serp), [ceo of adobe invented pdf John Warnock](https://www.google.com/search?q=ceo+of+adobe+invented+pdf+John+Warnock%2C&sca_esv=6a102af87d5bf95e&sca_upv=1&sxsrf=ACQVn092h-1zpdQfkfhqnjCnMyjtSN__6w%3A1714320957113&ei=PXYuZu6zBoj97_UPp6On6Ac&ved=0ahUKEwiuxredp-WFAxWI_rsIHafRCX0Q4dUDCBA&uact=5&oq=ceo+of+adobe+invented+pdf+John+Warnock%2C&gs_lp=Egxnd3Mtd2l6LXNlcnAiJ2NlbyBvZiBhZG9iZSBpbnZlbnRlZCBwZGYgSm9obiBXYXJub2NrLDIFECEYoAFItA5QJViqCHABeAGQAQCYAYcBoAGCAqoBAzAuMrgBA8gBAPgBAfgBApgCA6ACpwLCAgoQABiwAxjWBBhHmAMAiAYBkAYIkgcDMS4yoAeaBg&sclient=gws-wiz-serp)|
|3) Moving Objects in Space           |  [![video 3](https://ytcards.demolab.com/?id=wArGifkRD2A " ")](https://www.youtube.com/watch?v=wArGifkRD2A)    | [pinpoin camera]()   | 
|4) Rotations About an Arbitrary Axis |  [![video 4](https://ytcards.demolab.com/?id=gRVxv8kWl0Q " ")](https://www.youtube.com/watch?v=gRVxv8kWl0Q)    |  [mvc in cg](https://www.cs.cmu.edu/~462/www/lectures/assn1_intro.pdf)  |
|5) The Camera Transform              |  [![video 5](https://ytcards.demolab.com/?id=mpTl003EXCY " ")](https://www.youtube.com/watch?v=mpTl003EXCY)   | [view pyramid](https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/basic_algo.pdf)   |
|6) Clipping                          |  [![video 6](https://ytcards.demolab.com/?id=og7hOFypKpQ " ")](https://www.youtube.com/watch?v=og7hOFypKpQ)   | [Cohen line clipping alogrithm](https://www.vbspu.ac.in/e-content/Cohen-Sutherland.pdf)|
|7) Depth Buffers and Ray Tracing     |  [![video 7](https://ytcards.demolab.com/?id=Xks1v4GNUiY " ")](https://www.youtube.com/watch?v=Xks1v4GNUiY)   |  [Depth buffer algorithm ](https://ocw.metu.edu.tr/pluginfile.php/1021/mod_resource/content/0/documents/lecturenotes_2007/week13_VisibleSurfaceDetection.pdf)  |
|8) Color and Shading                 |  [![video 8](https://ytcards.demolab.com/?id=TEjDYtkLRdQ " ")](https://www.youtube.com/watch?v=TEjDYtkLRdQ)   | [texas university notes](https://www.cs.utexas.edu/~bajaj/graphics2012/cs354/lectures/lect14.pdf) [university of washington notes](https://courses.cs.washington.edu/courses/cse576/book/ch6.pdf)| 
|9) Quaternions                       |  [![video 9](https://ytcards.demolab.com/?id=mHVwd8gYLnI " ")](https://www.youtube.com/watch?v=mHVwd8gYLnI)   | [Uc Davis](https://faculty.engineering.ucdavis.edu/farouki/wp-content/uploads/sites/51/2021/07/Quaternions-and-spatial-rotations.pdf) [Gimbal lock video](https://www.youtube.com/watch?v=zc8b2Jo7mno)  [3d rotations](http://15462.courses.cs.cmu.edu/fall2019content/lectures/07_3drotations/07_3drotations_slides.pdf) [quaternion universita Torino](https://tarini.di.unimi.it/teaching/3DVG2021/3dvg.03.2.math_rotations.pdf) | 
|10) Shading and Texturing            |  [![video 10](https://ytcards.demolab.com/?id=Is6D5rnWEvs " ")](https://www.youtube.com/watch?v=Is6D5rnWEvs)   | [Drexel Univerity Texture Mapping](https://www.cs.drexel.edu/~deb39/Classes/ICG/Lectures_new/L-13_TextureMapping.pdf)  | 
|11) The Hierarchical Modeling System |  [![video 11](https://ytcards.demolab.com/?id=D8ZYHXom0qk " ")](https://www.youtube.com/watch?v=D8ZYHXom0qk)    |  [MIT Hierarchical modeling ](https://ocw.mit.edu/courses/6-837-computer-graphics-fall-2012/2b1e96254c4dc35b2f5cb1d48714c6d4_MIT6_837F12_Lec04.pdf) [Basic Ray Tracing texas university ](https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-4.pdf)  [Anti aliasing Weimar University](https://www.uni-weimar.de/fileadmin/user/fak/medien/professuren/Computer_Graphics/12-antialiasing-16.pdf)| 
|12) Scan Conversion                  |  [![video 12](https://ytcards.demolab.com/?id=23HEwdcphg4 " ")](https://www.youtube.com/watch?v=23HEwdcphg4)   | [scan conversion](https://www.collegenote.net/notes/attachment/scan-conversion-algorithm-69#:~:text=%2D%20The%20process%20of%20representing%20continuous,points%20and%20the%20line%20equation.) [Scan conversion  + clipping](https://elearn.daffodilvarsity.edu.bd/pluginfile.php/748061/mod_resource/content/1/2.3_Scan_Conversion_Math.pdf)  |
|13) Curves and Surfaces              |  [![video 13](https://ytcards.demolab.com/?id=FTg1DUr7bhY " ")](https://www.youtube.com/watch?v=FTg1DUr7bhY)    | [Convex Hull Property of a curve](https://ti.inf.ethz.ch/ew/courses/CG13/lecture/Chapter%203.pdf) [Nurbs non uniform rational bspline](https://professional3dservices.com/blog/nurbs-modeling.html#:~:text=NURBS%2C%20stands%20for%20Non%2DUniform,generated%20through%20a%20mathematical%20formula.) |
|14) Visible Surface Algorithms       |  [![video 14](https://ytcards.demolab.com/?id=hmlWFi1TdbI " ")](https://www.youtube.com/watch?v=hmlWFi1TdbI)    |[1, painters algorithm](https://web.cs.wpi.edu/~emmanuel/courses/cs4731/C13/slides/lecture24.pdf) [2, Warsnock algorithm](https://graphics.cmlab.csie.ntu.edu.tw/~robin/courses/3dcg08/ppt/3dcg08_05vsd.pdf) |
|15) Ray Tracing                      |  [![video 15](https://ytcards.demolab.com/?id=Ahp6LDQnK4Y " ")](https://www.youtube.com/watch?v=Ahp6LDQnK4Y)    | |
|16) Subdivision Surfaces Part 1      |  [![video 16](https://ytcards.demolab.com/?id=9uscFr2Hht0 " ")](https://www.youtube.com/watch?v=9uscFr2Hht0)    | [DOO-SABIN SURFACES ](https://www.cs.unc.edu/~dm/UNC/COMP258/LECTURES/Doo-Sabin.pdf)  [Advanced data structures, aka Pointer hell!](https://web.mat.upc.edu/toni.susin/files/IntroductionComputerGraphicsRenato.pdf) |
|17) Subdivision Surfaces Part 2      |  [![video 17](https://ytcards.demolab.com/?id=THiF7-QxKXk " ")](https://www.youtube.com/watch?v=THiF7-QxKXk)    | [CATMULL-CLARK SURFACES](https://www.cs.unc.edu/~dm/UNC/COMP258/LECTURES/Catmull-Clark.pdf) [subdivision notes ](https://empslocal.ex.ac.uk/people/staff/reverson/uploads/COM3404/subdivision4.pdf)|
|18) Shadows Part 1                   |  [![video 18](https://ytcards.demolab.com/?id=kmdRmXuOjIY " ")](https://www.youtube.com/watch?v=kmdRmXuOjIY)   | [Ground Plane Shadows](https://www.cim.mcgill.ca/~langer/557/19-slides.pdf) [Volumes Shadows](https://www.cs.toronto.edu/~strider/docs/D18_AdvancedRayTracing.pdf) |
|19) Shadows Part 2                   |  [![video 19](https://ytcards.demolab.com/?id=qiJhB0fOY6I " ")](https://www.youtube.com/watch?v=qiJhB0fOY6I)   | [Depth Buffer shadows](https://web.cse.ohio-state.edu/~shen.94/781/Site/Slides_files/shadow.pdf) |
|20) Camera Motion                    |  [![video 20](https://ytcards.demolab.com/?id=HAJv25Afsz8 " ")](https://www.youtube.com/watch?v=HAJv25Afsz8)   | [Catmull-Rom curves](https://www.cs.utexas.edu/~fussell/courses/cs384g-spring2016/lectures/interpolating_curves.pdf) [Freguson curves](https://cg.cs.tsinghua.edu.cn/course/docs/chap5.pdf)|
|21) Branches in Computer Graphics    |  [![video 21](https://ytcards.demolab.com/?id=NEIJW3ZJ1GE " ")](https://www.youtube.com/watch?v=NEIJW3ZJ1GE)    | |
 
 
