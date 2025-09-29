; Auto-generated. Do not edit!


(cl:in-package robot_msgs-msg)


;//! \htmlinclude LowlevelMotorCmd.msg.html

(cl:defclass <LowlevelMotorCmd> (roslisp-msg-protocol:ros-message)
  ((id
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
    :initform 0.0)
   (Kvp
    :reader Kvp
    :initarg :Kvp
    :type cl:float
    :initform 0.0)
   (Kvi
    :reader Kvi
    :initarg :Kvi
    :type cl:float
    :initform 0.0))
)

(cl:defclass LowlevelMotorCmd (<LowlevelMotorCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LowlevelMotorCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LowlevelMotorCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msgs-msg:<LowlevelMotorCmd> is deprecated: use robot_msgs-msg:LowlevelMotorCmd instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:id-val is deprecated.  Use robot_msgs-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'q-val :lambda-list '(m))
(cl:defmethod q-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:q-val is deprecated.  Use robot_msgs-msg:q instead.")
  (q m))

(cl:ensure-generic-function 'dq-val :lambda-list '(m))
(cl:defmethod dq-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:dq-val is deprecated.  Use robot_msgs-msg:dq instead.")
  (dq m))

(cl:ensure-generic-function 'tau-val :lambda-list '(m))
(cl:defmethod tau-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:tau-val is deprecated.  Use robot_msgs-msg:tau instead.")
  (tau m))

(cl:ensure-generic-function 'Kp-val :lambda-list '(m))
(cl:defmethod Kp-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kp-val is deprecated.  Use robot_msgs-msg:Kp instead.")
  (Kp m))

(cl:ensure-generic-function 'Kd-val :lambda-list '(m))
(cl:defmethod Kd-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kd-val is deprecated.  Use robot_msgs-msg:Kd instead.")
  (Kd m))

(cl:ensure-generic-function 'Kvp-val :lambda-list '(m))
(cl:defmethod Kvp-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kvp-val is deprecated.  Use robot_msgs-msg:Kvp instead.")
  (Kvp m))

(cl:ensure-generic-function 'Kvi-val :lambda-list '(m))
(cl:defmethod Kvi-val ((m <LowlevelMotorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:Kvi-val is deprecated.  Use robot_msgs-msg:Kvi instead.")
  (Kvi m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LowlevelMotorCmd>) ostream)
  "Serializes a message object of type '<LowlevelMotorCmd>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Kvp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Kvi))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LowlevelMotorCmd>) istream)
  "Deserializes a message object of type '<LowlevelMotorCmd>"
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Kvp) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Kvi) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LowlevelMotorCmd>)))
  "Returns string type for a message object of type '<LowlevelMotorCmd>"
  "robot_msgs/LowlevelMotorCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LowlevelMotorCmd)))
  "Returns string type for a message object of type 'LowlevelMotorCmd"
  "robot_msgs/LowlevelMotorCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LowlevelMotorCmd>)))
  "Returns md5sum for a message object of type '<LowlevelMotorCmd>"
  "287e30467db2eeba6fc4bc80506a1206")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LowlevelMotorCmd)))
  "Returns md5sum for a message object of type 'LowlevelMotorCmd"
  "287e30467db2eeba6fc4bc80506a1206")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LowlevelMotorCmd>)))
  "Returns full string definition for message of type '<LowlevelMotorCmd>"
  (cl:format cl:nil "# uint8 mode           # motor target mode~%# float32 q            # motor target position~%# float32 dq           # motor target velocity~%# float32 tau          # motor target torque~%# float32 Kp           # motor spring stiffness coefficient~%# float32 Kd           # motor damper coefficient~%# uint32[3] reserve    # motor target torque~%~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%float32 Kvp~%float32 Kvi~%#uint8 rv #反转参数~%# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LowlevelMotorCmd)))
  "Returns full string definition for message of type 'LowlevelMotorCmd"
  (cl:format cl:nil "# uint8 mode           # motor target mode~%# float32 q            # motor target position~%# float32 dq           # motor target velocity~%# float32 tau          # motor target torque~%# float32 Kp           # motor spring stiffness coefficient~%# float32 Kd           # motor damper coefficient~%# uint32[3] reserve    # motor target torque~%~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%float32 Kvp~%float32 Kvi~%#uint8 rv #反转参数~%# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LowlevelMotorCmd>))
  (cl:+ 0
     1
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LowlevelMotorCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'LowlevelMotorCmd
    (cl:cons ':id (id msg))
    (cl:cons ':q (q msg))
    (cl:cons ':dq (dq msg))
    (cl:cons ':tau (tau msg))
    (cl:cons ':Kp (Kp msg))
    (cl:cons ':Kd (Kd msg))
    (cl:cons ':Kvp (Kvp msg))
    (cl:cons ':Kvi (Kvi msg))
))
