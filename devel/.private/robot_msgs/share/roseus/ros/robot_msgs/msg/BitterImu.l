;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::BitterImu)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'BitterImu (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::BITTERIMU")
  (make-package "ROBOT_MSGS::BITTERIMU"))

(in-package "ROS")
;;//! \htmlinclude BitterImu.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass robot_msgs::BitterImu
  :super ros::object
  :slots (_header _quat _angular_vel_local _linear_acc_local _orientation_cov _angular_vel_cov _linear_acc_cov ))

(defmethod robot_msgs::BitterImu
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:quat __quat) (make-array 4 :initial-element 0.0 :element-type :float))
    ((:angular_vel_local __angular_vel_local) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:linear_acc_local __linear_acc_local) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:orientation_cov __orientation_cov) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:angular_vel_cov __angular_vel_cov) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:linear_acc_cov __linear_acc_cov) (make-array 9 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _quat __quat)
   (setq _angular_vel_local __angular_vel_local)
   (setq _linear_acc_local __linear_acc_local)
   (setq _orientation_cov __orientation_cov)
   (setq _angular_vel_cov __angular_vel_cov)
   (setq _linear_acc_cov __linear_acc_cov)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:quat
   (&optional __quat)
   (if __quat (setq _quat __quat)) _quat)
  (:angular_vel_local
   (&optional __angular_vel_local)
   (if __angular_vel_local (setq _angular_vel_local __angular_vel_local)) _angular_vel_local)
  (:linear_acc_local
   (&optional __linear_acc_local)
   (if __linear_acc_local (setq _linear_acc_local __linear_acc_local)) _linear_acc_local)
  (:orientation_cov
   (&optional __orientation_cov)
   (if __orientation_cov (setq _orientation_cov __orientation_cov)) _orientation_cov)
  (:angular_vel_cov
   (&optional __angular_vel_cov)
   (if __angular_vel_cov (setq _angular_vel_cov __angular_vel_cov)) _angular_vel_cov)
  (:linear_acc_cov
   (&optional __linear_acc_cov)
   (if __linear_acc_cov (setq _linear_acc_cov __linear_acc_cov)) _linear_acc_cov)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[4] _quat
    (* 8    4)
    ;; float64[3] _angular_vel_local
    (* 8    3)
    ;; float64[3] _linear_acc_local
    (* 8    3)
    ;; float64[9] _orientation_cov
    (* 8    9)
    ;; float64[9] _angular_vel_cov
    (* 8    9)
    ;; float64[9] _linear_acc_cov
    (* 8    9)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[4] _quat
     (dotimes (i 4)
       (sys::poke (elt _quat i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _angular_vel_local
     (dotimes (i 3)
       (sys::poke (elt _angular_vel_local i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[3] _linear_acc_local
     (dotimes (i 3)
       (sys::poke (elt _linear_acc_local i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _orientation_cov
     (dotimes (i 9)
       (sys::poke (elt _orientation_cov i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _angular_vel_cov
     (dotimes (i 9)
       (sys::poke (elt _angular_vel_cov i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[9] _linear_acc_cov
     (dotimes (i 9)
       (sys::poke (elt _linear_acc_cov i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[4] _quat
   (dotimes (i (length _quat))
     (setf (elt _quat i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _angular_vel_local
   (dotimes (i (length _angular_vel_local))
     (setf (elt _angular_vel_local i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[3] _linear_acc_local
   (dotimes (i (length _linear_acc_local))
     (setf (elt _linear_acc_local i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _orientation_cov
   (dotimes (i (length _orientation_cov))
     (setf (elt _orientation_cov i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _angular_vel_cov
   (dotimes (i (length _angular_vel_cov))
     (setf (elt _angular_vel_cov i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; float64[9] _linear_acc_cov
   (dotimes (i (length _linear_acc_cov))
     (setf (elt _linear_acc_cov i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;;
   self)
  )

(setf (get robot_msgs::BitterImu :md5sum-) "0f4e8b4bfb725baef44f23478818d1c0")
(setf (get robot_msgs::BitterImu :datatype-) "robot_msgs/BitterImu")
(setf (get robot_msgs::BitterImu :definition-)
      "# 自定义IMU消息格式
Header header # ROS标准消息头

# 四元数姿态 (x, y, z, w)
float64[4] quat

# 角速度 (单位: rad/s)
float64[3] angular_vel_local

# 线性加速度 (单位: m/s²)
float64[3] linear_acc_local

# 协方差矩阵 (3x3, 按行优先展开)
float64[9] orientation_cov # 姿态协方差
float64[9] angular_vel_cov # 角速度协方差
float64[9] linear_acc_cov # 加速度协方差
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



(provide :robot_msgs/BitterImu "0f4e8b4bfb725baef44f23478818d1c0")


