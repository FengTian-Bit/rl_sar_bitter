;; Auto-generated. Do not edit!


(when (boundp 'robot_msgs::Observation)
  (if (not (find-package "ROBOT_MSGS"))
    (make-package "ROBOT_MSGS"))
  (shadow 'Observation (find-package "ROBOT_MSGS")))
(unless (find-package "ROBOT_MSGS::OBSERVATION")
  (make-package "ROBOT_MSGS::OBSERVATION"))

(in-package "ROS")
;;//! \htmlinclude Observation.msg.html


(defclass robot_msgs::Observation
  :super ros::object
  :slots (_ang_vel _gravity_vec _commands _dof_pos _dof_vel _actions _obs ))

(defmethod robot_msgs::Observation
  (:init
   (&key
    ((:ang_vel __ang_vel) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:gravity_vec __gravity_vec) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:commands __commands) (make-array 3 :initial-element 0.0 :element-type :float))
    ((:dof_pos __dof_pos) (make-array 16 :initial-element 0.0 :element-type :float))
    ((:dof_vel __dof_vel) (make-array 16 :initial-element 0.0 :element-type :float))
    ((:actions __actions) (make-array 16 :initial-element 0.0 :element-type :float))
    ((:obs __obs) (make-array 57 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _ang_vel __ang_vel)
   (setq _gravity_vec __gravity_vec)
   (setq _commands __commands)
   (setq _dof_pos __dof_pos)
   (setq _dof_vel __dof_vel)
   (setq _actions __actions)
   (setq _obs __obs)
   self)
  (:ang_vel
   (&optional __ang_vel)
   (if __ang_vel (setq _ang_vel __ang_vel)) _ang_vel)
  (:gravity_vec
   (&optional __gravity_vec)
   (if __gravity_vec (setq _gravity_vec __gravity_vec)) _gravity_vec)
  (:commands
   (&optional __commands)
   (if __commands (setq _commands __commands)) _commands)
  (:dof_pos
   (&optional __dof_pos)
   (if __dof_pos (setq _dof_pos __dof_pos)) _dof_pos)
  (:dof_vel
   (&optional __dof_vel)
   (if __dof_vel (setq _dof_vel __dof_vel)) _dof_vel)
  (:actions
   (&optional __actions)
   (if __actions (setq _actions __actions)) _actions)
  (:obs
   (&optional __obs)
   (if __obs (setq _obs __obs)) _obs)
  (:serialization-length
   ()
   (+
    ;; float32[3] _ang_vel
    (* 4    3)
    ;; float32[3] _gravity_vec
    (* 4    3)
    ;; float32[3] _commands
    (* 4    3)
    ;; float32[16] _dof_pos
    (* 4    16)
    ;; float32[16] _dof_vel
    (* 4    16)
    ;; float32[16] _actions
    (* 4    16)
    ;; float32[57] _obs
    (* 4    57)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[3] _ang_vel
     (dotimes (i 3)
       (sys::poke (elt _ang_vel i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _gravity_vec
     (dotimes (i 3)
       (sys::poke (elt _gravity_vec i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[3] _commands
     (dotimes (i 3)
       (sys::poke (elt _commands i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[16] _dof_pos
     (dotimes (i 16)
       (sys::poke (elt _dof_pos i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[16] _dof_vel
     (dotimes (i 16)
       (sys::poke (elt _dof_vel i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[16] _actions
     (dotimes (i 16)
       (sys::poke (elt _actions i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[57] _obs
     (dotimes (i 57)
       (sys::poke (elt _obs i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[3] _ang_vel
   (dotimes (i (length _ang_vel))
     (setf (elt _ang_vel i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _gravity_vec
   (dotimes (i (length _gravity_vec))
     (setf (elt _gravity_vec i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[3] _commands
   (dotimes (i (length _commands))
     (setf (elt _commands i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[16] _dof_pos
   (dotimes (i (length _dof_pos))
     (setf (elt _dof_pos i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[16] _dof_vel
   (dotimes (i (length _dof_vel))
     (setf (elt _dof_vel i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[16] _actions
   (dotimes (i (length _actions))
     (setf (elt _actions i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[57] _obs
   (dotimes (i (length _obs))
     (setf (elt _obs i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get robot_msgs::Observation :md5sum-) "1cf74daf5018ef55d2264614972f54c9")
(setf (get robot_msgs::Observation :datatype-) "robot_msgs/Observation")
(setf (get robot_msgs::Observation :definition-)
      "#可单取出来
float32[3] ang_vel   # 角速度 wx, wy, wz
float32[3] gravity_vec  
float32[3] commands
float32[16] dof_pos
float32[16] dof_vel
float32[16] actions
#总观测量
float32[57] obs

")



(provide :robot_msgs/Observation "1cf74daf5018ef55d2264614972f54c9")


