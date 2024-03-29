#!/usr/bin/env python3

import tkinter as tk
from tkinter import Entry, Label, Button
import rospy
from std_msgs.msg import String

class GUI:

    def __init__(self):
        self.publish_mode = False
        self.publish_goal = False
        self.a = None
        self.b = None
        rospy.init_node("gui_node")
        self.pub_mode = rospy.Publisher("interrupt_event",String, queue_size = 10)
        self.pub_goal = rospy.Publisher("interrupt_event2", String, queue_size = 1)
        self.window = tk.Tk()
        self.window.title("immersion GUI")
        self.window.geometry("600x900+600+0")

        manual_button = Button(self.window, text="Manual Mode", width=35,height=10, command = self.manual_button_clicked)
        manual_button.grid(row=1, column=1)

        auto_button = Button(self.window, text="Auto Mode", width=35 ,height=10 ,command = self.auto_button_clicked)
        auto_button.grid(row=1, column=2)

        stop_button = Button(self.window, text="Stop",width= 70, height=10 , command = self.stop_button_clicked)
        stop_button.grid(row=3, column=1, columnspan=2, sticky='w')

        goal_a_button = Button(self.window, text="Move_To_GoalA",width= 35, height=10 , command = self.goal_a_clicked)
        goal_a_button.grid(row=2, column=1)

        goal_b_button = Button(self.window, text="Move_To_GoalB",width= 35, height=10 , command = self.goal_b_clicked)
        goal_b_button.grid(row=2, column=2)


        # rospy.Timer(rospy.Duration(1.0/ 1500.0), self.TimerCB)
        self.window.mainloop()
        

    def manual_button_clicked(self):
        self.publish_mode = True
        rospy.loginfo("Manual Mode Started")
        a = String()
        a.data = "manual"
        self.pub_mode.publish(a)
        # self.a = a
    def auto_button_clicked(self):
        self.publish_mode = True
        rospy.loginfo("Auto Mode Started")
        self.pub_mode.publish("auto")
        # self.a = "auto"

    def stop_button_clicked(self):
        self.publish_goal = True
        rospy.loginfo("Stop")
        self.pub_goal.publish("stop")
        # self.b = "stop"

    def goal_a_clicked(self):
        self.publish_goal = True
        rospy.loginfo("Move To Goal_A")
        self.pub_goal.publish("Goal_A")
        # self.b = "Goal_A"

    def goal_b_clicked(self):
        self.publish_goal = True
        rospy.loginfo("Move To Goal_B")
        self.pub_goal.publish("Goal_B")
        # self.b = "Goal_B"

    # def TimerCB(self, event):
    #     if self.publish_mode and self.a != None:
    #         self.pub_mode.publish(self.a)

    #     if self.publish_goal and self.b != None:
    #         self.pub_goal.publish(self.b)
        

    
start = GUI()



