import random
import time
from pprint import pprint

#Program: tablebalancer.py
#Function: Places blocks of ascending weights onto a balance table, attempts to keep the table balanced while placing all of the blocks. 
#Use: Table must be > 2x2. Table is always a square. 
#Use: python blockplacer.py

user = int(input("Please enter how big you want the table to be (single int value): "))
print(user)
print("\n")

if(user < 3):
    print("ERROR: Table must be larger than 2x2.")
    time.sleep(3)
    exit()

#The array that the blocks will be dropped onto. 
arr = [[0 for i in range(user)] for j in range(user)]
print("The array the blocks will be dropped onto.")
pprint(arr)
print("\n")

#The location of the Balancing Point of the Table.
pole = [user/2 , user/2]
print("The Balancing Point: " + str(pole))

#Orange square == Okay zone
orange_zone = [pole[0]-1, pole[1]+1]
print("The Orange Zone: " + str(orange_zone))

#The Center of Mass. Starts equal to the balancing point.
cg = pole
print("The Initial Center of Mass: " + str(cg))
print("\n")

#Init The blocks that will be dropped by the AI.
blocks = [i+1 for i in range(user*user)]
print("The blocks that will be dropped.")
print(blocks)
print("\n")

#***********************************************************************
#Some variable declarations...
placed = {}
xtop = 0
ytop = 0
xbottom = 0
ybottom = 0

#Fill arr. For each block, starting with the heaviest, look for position in table where the cg is in the orange zone, place.
for block in reversed(blocks):
    currentblock = block

    for x in range(user):
        for y in range(user):
            
            #Find the Center of Mass
            for block in placed:
               
                xtop = (placed[block]['value'] * placed[block]['x']) + xtop
                ytop = (placed[block]['value'] * placed[block]['y']) + ytop
                xbottom = placed[block]['value'] + xbottom
                ybottom = placed[block]['value'] + ybottom
                
            cg[0] = ((currentblock * x) + xtop) / (currentblock + xbottom)
            cg[1] = ((currentblock * y) + ytop) / (currentblock + ybottom)

            #Refesh all our variables...;_;
            xtop = 0
            ytop = 0
            xbottom = 0
            ybottom = 0

            #if center of mass is inside the range of orange and nobody else is already placed here.
            if(arr[x][y] == 0):
                if(orange_zone[0] <= cg[0] <= orange_zone[1] and orange_zone[0] <= cg[1] <= orange_zone[1]):
                    
                    #Place block
                    placed[currentblock] = {}
                    placed[currentblock]['x'] = x #So we have a list of all placed blocks.
                    placed[currentblock]['y'] = y
                    placed[currentblock]['value'] = block

                    arr[x][y] = currentblock
                    break

        else:
            continue
        break


#Print result.
print("The FINAL ARRAY")

for i in range(user):
    for j in range(user):
        print("%4.0f" % arr[i][j], end = '')
    print("")

print("\n")
input('Press enter to exit.')

#Equation for calculating the center of mass on a plane. 
#xmass = (columncoor * weight + ...etc)/weights...
#xmass = (col*w + col*w + col*w +)/w
#ymass = (row*w + row*w + row*w +)/w

# Place heaviest block at middle.
#AI checks next heaviest block at all positions, places where balance is closest to zero. If no safe place, go to next weight.
#Should not need to back track because the blocks are placed in order from heaviest to lightest, so there should always be a safe place.
