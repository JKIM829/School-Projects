#(={3})([\s\w.]*)\s(vs\.)([.\s\w]*,)\s([\d-]*)\s={3} REGEX for matching === SomeTeam vs. Other Team, Date ===
#([\w]*)\s([\w]*)\sbatted\s(\d)\stimes\swith\s(\d)\shits\sand\s(\d)\sruns
#URL for assignment guidelines: https://classes.engineering.wustl.edu/cse330/index.php/Module_4

import sys, os

import re

import operator

if len(sys.argv) < 2:
	sys.exit("Please input an argument in the format 'python %s input_file.txt'" % sys.argv[0])
 
filename = sys.argv[1]
 
if not os.path.exists(filename):
	sys.exit("Error: File '%s' not found" % sys.argv[1])


Players_List = []

class Player:
    name = ""
    batted = 0.000
    hits = 0.000
    runs = 0.000
    date = 0
    avg = 0
    
    def __init__(self, n, bat, hit, run, d):
        self.name = n
        self.batted = bat
        self.hits = hit
        self.runs = run
        self.date = d
    
    #Equality operator overloaded    
    def __eq__(self, other):
        if isinstance(other, Player):
            return self.name == other.name
        else:
            return False
        
    #Inequality operator overloaded
    def __ne__(self, other):
        return not self.__eq__(other)
     
    #Takes the objects hits over its batted, and rounds it to 3 decimal places    
    def compute_avg(self):
        temp= float(self.hits)/float(self.batted)
        self.avg = round(temp,3)
        return self.avg

    def get_definition(self):
        return self.name
		
    def get_avg(self):
        return self.avg
	

   #If player read from file is already in Players_List, add their batted & hits to this player's total.
    def append(self,other_player):     
        self.batted += other_player.batted
        self.hits += other_player.hits
        self.runs += other_player.runs
    
    


seasonName_regex = re.compile(r"={3}([\s\w.]*)\svs\.([.\s\w]*),\s([\d]*)([\d-]*)\s={3}")

def SeasonName(test):
    match = seasonName_regex.match(test)
    if match is not None:
        return match.group(3)
    else:
        return False


player_regex = re.compile(r"([\w]*\s[\w]*)\sbatted\s(\d)\stimes\swith\s(\d)\shits\sand\s(\d)\sruns")

#tries to parse a player based on raw string input using regular expressions
def player_parse(test, date):
    match = player_regex.match(test)
    if match is not None:
        new_player = Player(match.group(1), int(match.group(2)), int(match.group(3)), int(match.group(4)), int(date))
        return new_player
    else:
        return False
    
 #If list is empty, add the first player. Otherwise, iterate through the list to make sure no duplicates, append the player or increment an already existing entry   
def Calculate_Players(p):
    if(len(Players_List) == 0):
        Players_List.append(p)
        return
    
    for player in Players_List:
        if player == p:
            player.append(p)
            return

    Players_List.append(p)
      

date = 0

#Use regular expressions to parse through lines. 
with open(filename) as f:
    for line in f:
        try_date = SeasonName(line.rstrip())
        try_player=player_parse(line.rstrip(), date)
        
        if try_date != False:
            date = try_date
        
        if try_player != False and date != 0:
            Calculate_Players(try_player)
      
#After file is read, compute each players avg        
for player in (Players_List):
    player.compute_avg()
    
#Sort the list by player averages
Players_List.sort(key=operator.attrgetter('avg'), reverse = True)

#Output
#NOTE: I output as a 3-decimal-places float, but the value of the players' avg is rounded (not truncated) in the compute_avg() function
for player in (Players_List):
    print "%s: %.3f  " % (player.get_definition(), player.get_avg())





            
