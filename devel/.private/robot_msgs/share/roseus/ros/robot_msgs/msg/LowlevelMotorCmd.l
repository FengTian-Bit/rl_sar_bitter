;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::LowlevelMotorCmd)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'LowlevelMotorCmd (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::LOWLEVELMOTORCMD")
  (make-package "ROBOT_MSGS::LOWLEVELMOTORCMD"))

(in-package "ROS")
;;//! \htmlinclude LowlevelMotorCmd.msg.html


(defclass robot_msgs::LowlevelMotorCmd
  :super ros::object
  :slots (_id _q _dq _tau _Kp _Kd _Kvp _Kvi ))

(defmethod robot_msgs::LowlevelMotorCmd
  (:init
   (&key
    ((:id __id) 0)
    ((:q __q) 0.0)
    ((:dq __dq) 0.0)
    ((:tau __tau) 0.0)
    ((:Kp __Kp) 0.0)
    ((:Kd __Kd) 0.0)
    ((:Kvp __Kvp) 0.0)
    ((:Kvi __Kvi) 0.0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _q (float __q))
   (setq _dq (float __dq))
   (setq _tau (float __tau))
   (setq _Kp (float __Kp))
   (setq _Kd (float __Kd))
   (setq _Kvp (float __Kvp))
   (setq _Kvi (float __Kvi))
   self)
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
  (:Kvp
   (&optional __Kvp)
   (if __Kvp (setq _Kvp __Kvp)) _Kvp)
  (:Kvi
   (&optional __Kvi)
   (if __Kvi (setq _Kvi __Kvi)) _Kvi)
  (:serialization-length
   ()
   (+
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
    ;; float32 _Kvp
    4
    ;; float32 _Kvi
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
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
     ;; float32 _Kvp
       (sys::poke _Kvp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _Kvi
       (sys::poke _Kvi (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
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
   ;; float32 _Kvp
     (setq _Kvp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _Kvi
     (setq _Kvi (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get robot_msgs::LowlevelMotorCmd :md5sum-) "287e30467db2eeba6fc4bc80506a1206")
(setf (get robot_msgs::LowlevelMotorCmd :datatype-) "robot_msgs/LowlevelMotorCmd")
(setf (get robot_msgs::LowlevelMotorCmd :definition-)
      "# uint8 mode           # motor target mode
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



(provide :robot_msgs/LowlevelMotorCmd "287e30467db2eeba6fc4bc80506a1206")


