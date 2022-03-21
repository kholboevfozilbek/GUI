# GUI

Alright, lets get this GUI thing, get sorted out.  \
Honestly, I have been continiously searching how to begin GUI topic. 
By which language and framework combination I start with, would suit the me (as complete beginner to GUI)
I found out these ones 
  C# (.NET, WPF, WindowsForms Uno Mono ... ) -> perfect easy, advanced GUI features, native look(since Microsoft), low or no code at all,  but only for windows
  Java (JavaFx, Swing ... ) -> cross-platfrom, a little learning required, moderate GUI features, but some performace issues 
  C, C++
      -> frameworks (Qt, wxWidgets, gtkmm, GTK+, Juce), old-school look, good-enough GUI, cross-platform (I guess) but solid performace
      -> going hard way (hard coded libraries, SDL2, openGL, some rendering stuff. Everything is by hand)
      
After I come to conclusion that none of them would work unless I really understand the underlaying processes (the behind the scenes). 
Like what is GUI and what it is supposed to do, how perfect GUI should be and what it should contain and how the design and conecpt of software should be like.
Like what is window, what is surface,  texture and what is shapes, how computers treats images and puts to the screen nicely (methods)
what is events (types) and how it is being handled? (mouse, keyboard, sound ... ). 

Well after some digging, I found that all these GUI facilities (frameworks and libraries) is nothing but abstraction for you such that you would not have to 
hard-code everything by hand(craziness 100%), you just drag-and-dropp and it would work. 
but behind the scenes it still handles it in the same way(professionally) but also linking part is also a bonus for you in the way that you would not have to link all those 
dependencies and all that.
