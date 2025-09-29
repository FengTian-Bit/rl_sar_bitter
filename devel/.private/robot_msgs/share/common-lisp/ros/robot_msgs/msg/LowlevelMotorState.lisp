; Auto-generated. Do not edit!


(cl:in-package robot_msgs-msg)


;//! \htmlinclude LowlevelMotorState.msg.html

(cl:defclass <LowlevelMotorState> (roslisp-msg-protocol:ros-message)
  ((stamp
    :reader stamp
    :initarg :stamp
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (q
    :reader q
    :initarg :q
    :type cl:float
    :initform 0.0)
   (dq
    :reader dq
    :initarg :dq
    :type cl:float
    :initform 0.0)
   (tau
    :reader tau
    :initarg :tau
    :type cl:float
    :initform 0.0)
   (Kp
    :reader Kp
    :initarg :Kp
    :type cl:float
    :initform 0.0)
   (Kd
    :reader Kd
    :initarg :Kd
    :type cl:float
    :initform 0.0))
)

(cl:defclass LowlevelMotorState (<LowlevelMotorState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LowlevelMotorState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LowlevelMotorState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msgs-msg:<LowlevelMotorState> is deprecated: use robot_msgs-msg:LowlevelMotorState instead.")))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:stamp-val is deprecated.  Use robot_msgs-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:id-val is deprecated.  Use robot_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:q-val is deprecated.  Use robot_msgs-msg:q instead.")
  (q m))

(cl:ensure-generic-function 'dq-val :lambda-list '(m))
(cl:defmethod dq-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:dq-val is deprecated.  Use robot_msgs-msg:dq instead.")
  (dq m))

(cl:ensure-generic-function 'tau-val :lambda-list '(m))
(cl:defmethod tau-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:tau-val is deprecated.  Use robot_msgs-msg:tau instead.")
  (tau m))

(cl:ensure-generic-function 'Kp-val :lambda-list '(m))
(cl:defmethod Kp-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kp-val is deprecated.  Use robot_msgs-msg:Kp instead.")
  (Kp m))

(cl:ensure-generic-function 'Kd-val :lambda-list '(m))
(cl:defmethod Kd-val ((m <LowlevelMotorState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kd-val is deprecated.  Use robot_msgs-msg:Kd instead.")
  (Kd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LowlevelMotorState>) ostream)
  "Serializes a message object of type '<LowlevelMotorState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'stamp) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'q))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dq))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tau))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Kp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Kd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LowlevelMotorState>) istream)
  "Deserializes a message object of type '<LowlevelMotorState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'stamp) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'q) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dq) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tau) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Kp) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Kd) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LowlevelMotorState>)))
  "Returns string type for a message object of type '<LowlevelMotorState>"
  "robot_msgs/LowlevelMotorState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LowlevelMotorState)))
  "Returns string type for a message object of type 'LowlevelMotorState"
  "robot_msgs/LowlevelMotorState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LowlevelMotorState>)))
  "Returns md5sum for a message object of type '<LowlevelMotorState>"
  "7be5bb1e36dfe9f0c461b081b3c9bca9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LowlevelMotorState)))
  "Returns md5sum for a message object of type 'LowlevelMotorState"
  "7be5bb1e36dfe9f0c461b081b3c9bca9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LowlevelMotorState>)))
  "Returns full string definition for message of type '<LowlevelMotorState>"
  (cl:format cl:nil "#时间戳~%std_msgs/Header stamp~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%#uint8 rv~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LowlevelMotorState)))
  "Returns full string definition for message of type 'LowlevelMotorState"
  (cl:format cl:nil "#时间戳~%std_msgs/Header stamp~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%#uint8 rv~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LowlevelMotorState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'stamp))
     1
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LowlevelMotorState>))
  "Converts a ROS message object to a list"
  (cl:list 'LowlevelMotorState
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':id (id msg))
    (cl:cons ':q (q msg))
    (cl:cons ':dq (dq msg))
    (cl:cons ':tau (tau msg))
    (cl:cons ':Kp (Kp msg))
    (cl:cons ':Kd (Kd msg))
))
