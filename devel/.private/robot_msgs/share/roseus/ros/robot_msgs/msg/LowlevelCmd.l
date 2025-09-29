;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::LowlevelCmd)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'LowlevelCmd (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::LOWLEVELCMD")
  (make-package "ROBOT_MSGS::LOWLEVELCMD"))

(in-package "ROS")
;;//! \htmlinclude LowlevelCmd.msg.html


(defclass robot_msgs::LowlevelCmd
  :super ros::object
  :slots (_motorCmd ))

(defmethod robot_msgs::LowlevelCmd
  (:init
   (&key
    ((:motorCmd __motorCmd) (let (r) (dotimes (i 16) (push (instance robot_msgs::LowlevelMotorCmd :init) r)) r))
    )
   (send-super :init)
   (setq _motorCmd __motorCmd)
   self)
  (:motorCmd
   (&rest __motorCmd)
   (if (keywordp (car __motorCmd))
       (send* _motorCmd __motorCmd)
     (progn
       (if __motorCmd (setq _motorCmd (car __motorCmd)))
       _motorCmd)))
  (:serialization-length
   ()
   (+
    ;; robot_msgs/LowlevelMotorCmd[16] _motorCmd
    (apply #'+ (send-all _motorCmd :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; robot_msgs/LowlevelMotorCmd[16] _motorCmd
     (dolist (elem _motorCmd)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; robot_msgs/LowlevelMotorCmd[16] _motorCmd
   (dotimes (i 16)
     (send (elt _motorCmd i) :deserialize buf ptr-) (incf ptr- (send (elt _motorCmd i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get robot_msgs::LowlevelCmd :md5sum-) "2b8ca0cf47ba441d44c5cb8cd95d8693")
(setf (get robot_msgs::LowlevelCmd :datatype-) "robot_msgs/LowlevelCmd")
(setf (get robot_msgs::LowlevelCmd :definition-)
      "LowlevelMotorCmd[16] motorCmd
================================================================================
MSG: robot_msgs/LowlevelMotorCmd
# uint8 mode           # motor target mode
# float32 q            # motor target position
# float32 dq           # motor target velocity
# float32 tau          # motor target torque
# float32 Kp           # motor spring stiffness coefficient
# float32 Kd           # motor damper coefficient
# uint32[3] reserve    # motor target torque

# uint8 mode           # 电机当前模式
uint8 id                # 电机ID
float32 q            # 电机当前位置（弧度）
float32 dq           # 电机当前速度（弧度/秒）
float32 tau          # 当前输出扭矩（牛·米）
#Kp ，Kd，反转参数reverse
float32 Kp
float32 Kd
float32 Kvp
float32 Kvi
#uint8 rv #反转参数
# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）
")



(provide :robot_msgs/LowlevelCmd "2b8ca0cf47ba441d44c5cb8cd95d8693")


