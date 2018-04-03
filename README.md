# Cpp-Samples
Some of my C++ sample projects

### TextReversi
My first C++ project was an attempt at writing Reversi/Othello back in 2006; back before I knew better.  I found the source code for this project in a portfolio that I made during my time at ITT Technical Institute and uploaded it to GitHub. 12 years later, I finally completed the game, and more then I had originally intended!

The code first started off as procedural code and it only handled the pre-game, in game, and post game states in one massive monolithic main, but now the base uses a mix of Object Oriented/Procedural code and throws in some STL for good measure.  

The game was originally a PvP only game which was played on the same console, but the option is now available for a Human to play against the computer or to watch two AIs go head-to-head.  The architecture follows a state based design complete with: Intro, Main Menu, Display Rules, Setup New Game, Load Game, In Game, Game Over, and Exiting states.  These are all loaded and managed with a State Manager which is run within a game loop.  The pre, in, and post game states use a Game Context to share information between them.

Of particular interest to me is the game AI! Originally, it started as a simple "choose a random move from the available moves" which then led to designing a heuristic that has the computer choosing the key corner locations over randomly choosing.  The random move was then replaced with a MiniMax solution with the effect of the AI making a move that optimizes the availability of its future moves while minimizing its opponents moves.  The idea for using move mobility for the evaluation came from: http://home.datacomm.ch/t_wolf/tw/misc/reversi/html/index.html.
