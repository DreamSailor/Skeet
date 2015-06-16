###############################################################
# Program:
#     Project ##, ????
#     Brother Helfrich, CS165
# Author:
#     author one
#     author two
# Summary:
#     Enter a brief description of your program here! If you do any
#     extra credit, this would be a good place to describe it.
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################

###############################################################
# Programs:
#    pong:         The playable game
#    uiTest:       Simple driver program for the drawing interface
###############################################################
#pong : pong.o uiInteract.o uiDraw.o point.o
#	g++ -o pong pong.o uiInteract.o uiDraw.o point.o -L/System/Library/Frameworks -framework GLUT -L/System/Library/Frameworks -framework OpenGL
#	tar -cf pong.tar *.cpp *.h makefile

skeet : skeet.o uiDraw.o uiInteract.o point.o bullet.o
	g++ -o skeet skeet.o uiDraw.o uiInteract.o point.o -L/System/Library/Frameworks -framework GLUT -L/System/Library/Frameworks -framework OpenGL


##uiTest : uiTest.o uiDraw.o uiInteract.o point.o
##	g++ -o uiTest uiTest.o uiDraw.o uiInteract.o point.o -L/System/Library/Frameworks -framework GLUT -L/System/Library/Frameworks -framework OpenGL

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    uiTest.o      Driver program for uiDraw and uiTest
#    pong.o        Only the greatest game ever! (and it was for 20 years)  
###############################################################
uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

point.o : point.cpp point.h
	g++ -c point.cpp
	
#bullet.o : bullet.cpp bullet.h
#	g++ -c bullet.cpp

skeet.o : skeet.cpp point.h uiDraw.h uiInteract.h
	g++ -c skeet.cpp


##uiTest.o : uiTest.cpp point.h uiDraw.h uiInteract.h
##	g++ -c uiTest.cpp

#pong.o : pong.cpp uiDraw.h uiInteract.h point.h
#	g++ -c pong.cpp


###############################################################
# General rules
###############################################################
clean :
	rm uiTest pong *.o *.tar

all :  uiTest pong

