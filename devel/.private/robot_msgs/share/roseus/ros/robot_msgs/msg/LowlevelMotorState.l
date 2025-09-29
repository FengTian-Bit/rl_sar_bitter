;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::LowlevelMotorState)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'LowlevelMotorState (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::LOWLEVELMOTORSTATE")
  (make-package "ROBOT_MSGS::LOWLEVELMOTORSTATE"))

(in-package "ROS")
;;//! \htmlinclude LowlevelMotorState.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass robot_msgs::LowlevelMotorState
  :super ros::object
  :slots (_stamp _id _q _dq _tau _Kp _Kd ))

(defmethod robot_msgs::LowlevelMotorState
  (:init
   (&key
    ((:stamp __stamp) (instance std_msgs::Header :init))
    ((:id __id) 0)
    ((:q __q) 0.0)
    ((:dq __dq) 0.0)
    ((:tau __tau) 0.0)
    ((:Kp __Kp) 0.0)
    ((:Kd __Kd) 0.0)
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _id (round __id))
   (setq _q (float __q))
   (setq _dq (float __dq))
   (setq _tau (float __tau))
   (setq _Kp (float __Kp))
   (setq _Kd (float __Kd))
   self)
  (:stamp
   (&rest __stamp)
   (if (keywordp (car __stamp))
       (send* _stamp __stamp)
     (progn
       (if __stamp (setq _stamp (car __stamp)))
       _stamp)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:q
   (&optional __q)
   (if __q (setq _q __q)) _q)
  (:dq
   (&optional __dq)
   (if __dq (setq _dq __dq)) _dq)
  (:tau
   (&optional __tau)
   (if __tau (setq _tau __tau)) _tau)
  (:Kp
   (&optional __Kp)
   (if __Kp (setq _Kp __Kp)) _Kp)
  (:Kd
   (&optional __Kd)
   (if __Kd (setq _Kd __Kd)) _Kd)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _stamp
    (send _stamp :serialization-length)
    ;; uint8 _id
    1
    ;; float32 _q
    4
    ;; float32 _dq
    4
    ;; float32 _tau
    4
    ;; float32 _Kp
    4
    ;; float32 _Kd
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _stamp
       (send _stamp :serialize s)
     ;; uint8 _id
       (write-byte _id s)
     ;; float32 _q
       (sys::poke _q (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _dq
       (sys::poke _dq (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tau
       (sys::poke _tau (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Kp
       (sys::poke _Kp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Kd
       (sys::poke _Kd (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _stamp
     (send _stamp :deserialize buf ptr-) (incf ptr- (send _stamp :serialization-length))
   ;; uint8 _id
     (setq _id (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _q
     (setq _q (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _dq
     (setq _dq (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tau
     (setq _tau (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Kp
     (setq _Kp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Kd
     (setq _Kd (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_msgs::LowlevelMotorState :md5sum-) "7be5bb1e36dfe9f0c461b081b3c9bca9")
(setf (get robot_msgs::LowlevelMotorState :datatype-) "robot_msgs/LowlevelMotorState")
(setf (get robot_msgs::LowlevelMotorState :definition-)
      "#时间戳
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



(provide :robot_msgs/LowlevelMotorState "7be5bb1e36dfe9f0c461b081b3c9bca9")


