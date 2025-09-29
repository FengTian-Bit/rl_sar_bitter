;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::LowlevelState)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'LowlevelState (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::LOWLEVELSTATE")
  (make-package "ROBOT_MSGS::LOWLEVELSTATE"))

(in-package "ROS")
;;//! \htmlinclude LowlevelState.msg.html


(defclass robot_msgs::LowlevelState
  :super ros::object
  :slots (_motorState ))

(defmethod robot_msgs::LowlevelState
  (:init
   (&key
    ((:motorState __motorState) (let (r) (dotimes (i 16) (push (instance robot_msgs::LowlevelMotorState :init) r)) r))
    )
   (send-super :init)
   (setq _motorState __motorState)
   self)
  (:motorState
   (&rest __motorState)
   (if (keywordp (car __motorState))
       (send* _motorState __motorState)
     (progn
       (if __motorState (setq _motorState (car __motorState)))
       _motorState)))
  (:serialization-length
   ()
   (+
    ;; robot_msgs/LowlevelMotorState[16] _motorState
    (apply #'+ (send-all _motorState :serialization-length))
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; robot_msgs/LowlevelMotorState[16] _motorState
     (dolist (elem _motorState)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; robot_msgs/LowlevelMotorState[16] _motorState
   (dotimes (i 16)
     (send (elt _motorState i) :deserialize buf ptr-) (incf ptr- (send (elt _motorState i) :serialization-length))
     )
   ;;
   self)
  )

(setf (get robot_msgs::LowlevelState :md5sum-) "039d2d311ce4c771aaf577626734f296")
(setf (get robot_msgs::LowlevelState :datatype-) "robot_msgs/LowlevelState")
(setf (get robot_msgs::LowlevelState :definition-)
      "LowlevelMotorState[16] motorState
================================================================================
MSG: robot_msgs/LowlevelMotorState
#时间戳
std_msgs/Header stamp
# uint8 mode           # 电机当前模式
uint8 id                # 电机ID
float32 q            # 电机当前位置（弧度）
float32 dq           # 电机当前速度（弧度/秒）
float32 tau          # 当前输出扭矩（牛·米）
#Kp ，Kd，反转参数reverse
float32 Kp
float32 Kd
#uint8 rv



================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :robot_msgs/LowlevelState "039d2d311ce4c771aaf577626734f296")


