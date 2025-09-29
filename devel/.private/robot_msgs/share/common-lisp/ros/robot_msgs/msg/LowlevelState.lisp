; Auto-generated. Do not edit!


(cl:in-package robot_msgs-msg)


;//! \htmlinclude LowlevelState.msg.html

(cl:defclass <LowlevelState> (roslisp-msg-protocol:ros-message)
  ((motorState
    :reader motorState
    :initarg :motorState
    :type (cl:vector robot_msgs-msg:LowlevelMotorState)
   :initform (cl:make-array 16 :element-type 'robot_msgs-msg:LowlevelMotorState :initial-element (cl:make-instance 'robot_msgs-msg:LowlevelMotorState))))
)

(cl:defclass LowlevelState (<LowlevelState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LowlevelState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LowlevelState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msgs-msg:<LowlevelState> is deprecated: use robot_msgs-msg:LowlevelState instead.")))

(cl:ensure-generic-function 'motorState-val :lambda-list '(m))
(cl:defmethod motorState-val ((m <LowlevelState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:motorState-val is deprecated.  Use robot_msgs-msg:motorState instead.")
  (motorState m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LowlevelState>) ostream)
  "Serializes a message object of type '<LowlevelState>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'motorState))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LowlevelState>) istream)
  "Deserializes a message object of type '<LowlevelState>"
  (cl:setf (cl:slot-value msg 'motorState) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'motorState)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:make-instance 'robot_msgs-msg:LowlevelMotorState))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LowlevelState>)))
  "Returns string type for a message object of type '<LowlevelState>"
  "robot_msgs/LowlevelState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LowlevelState)))
  "Returns string type for a message object of type 'LowlevelState"
  "robot_msgs/LowlevelState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LowlevelState>)))
  "Returns md5sum for a message object of type '<LowlevelState>"
  "039d2d311ce4c771aaf577626734f296")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LowlevelState)))
  "Returns md5sum for a message object of type 'LowlevelState"
  "039d2d311ce4c771aaf577626734f296")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LowlevelState>)))
  "Returns full string definition for message of type '<LowlevelState>"
  (cl:format cl:nil "LowlevelMotorState[16] motorState~%================================================================================~%MSG: robot_msgs/LowlevelMotorState~%#时间戳~%std_msgs/Header stamp~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%#uint8 rv~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LowlevelState)))
  "Returns full string definition for message of type 'LowlevelState"
  (cl:format cl:nil "LowlevelMotorState[16] motorState~%================================================================================~%MSG: robot_msgs/LowlevelMotorState~%#时间戳~%std_msgs/Header stamp~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%#uint8 rv~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LowlevelState>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'motorState) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LowlevelState>))
  "Converts a ROS message object to a list"
  (cl:list 'LowlevelState
    (cl:cons ':motorState (motorState msg))
))
