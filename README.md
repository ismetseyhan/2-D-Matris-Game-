# 2-D-Matris-Game-
---------------INTRODUCTION------------------

In this experiment, you are expected to implement a game which is runned with
commands from an input file. This game is based on a fantastic adventure board game and runs
on a given multi-dimensional array. There will be two sides (monsters, heroes) and they will
attack to each other. After given commands are executed, your program should print related
outputs into a text file such as current situation of the map and status of the characters. Details
are explained below.
-----------BACKGROUND INFORMATION-----------

Adventure board games involve fantastical elements like heroes which explore the given
map and the monsters they encounter during this exploration. Both heroes and monsters have
different properties such as special attacks, health and they fight with each other accordingly.
In general, game is finished after given quest is accomplished.
Monsters are placed on some specified points and heroes can attack them if they
adjacent to their square. This combat takes place in an order like first all monsters attack to
their adjacent heroes in their spawn order and then all heroes attack to their adjacent monsters
in their spawn order vice versa. Therefore, if there is more than one monster adjacent to a
hero, the first spawned monster will attack first and so on. Similarly, heroes attack in their
spawn order to an adjacent monster.
Health is usually measured in hit points or health points, shortened to “HP”. When the
HP of a character reaches zero, it become incapacitated or die. Each hero and monster have
different attack powers and they give damage each other according to these attack powers.
Consequently, monster’s or hero’s HP is decreased according to attack’s “damage” value. If a
hero kills a monster, that hero gains one experience point, shortened to “XP”.


Note:
Argüments

gcc main.c -lm
./a.out chars.txt commands.txt output.txt
