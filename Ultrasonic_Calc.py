# Brian Wisniewski
# 6/12/2017
# Simple Timer Freq Calculator.
##############################################################
#                           USER INPUTS                      #
##############################################################
# Distance Object is from ultrasonic sensor.
D = 12; 
# Timer Counts        
Counts = 73063; 
##############################################################
#                   CALCULATIONS & CONSTANTS                 #          
##############################################################
CF = 39.3701;   # Conversion Factor inches to meters.
C = 340.29;     # Speed of sound.
# Calculated Timer Freq
# Distance Eq: D = ((1/Timer_Freq)*Counts) * (C*CF)/2
Timer_Freq = (2*D/C/CF/Counts)**(-1);
# Print Timer Freq
print('Timer Frequency: '  + str(Timer_Freq / 10**6) + ' [MHz]');