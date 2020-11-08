# BOTWMechanics

This is my current project. The idea behind it was to get used to working in Unreal Engine by recreating some of the rune powers from Breath of the Wild; Cryonis, Magnesis etc.

The project is written using a combination of C++ and blueprints. More specifically the game logic and player control is being run through C++ (classes are in the Source folder), but some of the Actors are using blueprints to control their behaviour, like the Cryonis blocks are using a Timeline to scale themselves when spawned.

The character model for the player was created by TalkingDrums and sourced from the Unreal Marketplace, everything else is being created by me(the landscape, water, animations etc). I'm creating the animations using Blender.

I'll try and add examples of each of the powers as they are added. Below is the Cryonis power that I am currently working on. It only works on water and only stays there for a limited amount of time.
 
![Demo](Demo/botw_ice.gif)

Next I think will be Magnesis, so watch this space.
