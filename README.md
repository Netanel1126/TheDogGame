# TheDogGame
TheDogGame is combined of 3 parts Server Client & Game

Server: 
1)responsible for managing multipool Clients and listen for Commands
2) is also responsible for holding all of the data (like scoreboard, Users) 3) in addition the server is responsible for matching 2 players for a game
4)the server will send Active Users or Scoreboard if requested by the users
5)The server will save the scoreboard and Users for future usage
6)The server will connect to the client using Tcp Socket

Client:
1)The Client will have to either Sing In or Log in 
2)The Client can see all active users 
3)The Client can start a game with a active user
4)The Client can start a random game
5)The Client can decline a game request

Game:
1)The Game uses P2P Udp Socket to send and recv messages between 2 users  
2)The Dog Game is a turn based puzzle game for two players,

How To Play:
Both players must first bury their 5 'bones' in the Backyard  by choosing the locations on the map
the 'bones' will by marked wit 'O' then the players will have 10 chances to 'dig' the other player bones
if player finds a 'bone' it will be marked with a 'O' and in the other player 'backyard' and your score will
rise by 100 else it will be marked with 'X' if player finds a 'bone' in your 'backyard' it with 'X'
