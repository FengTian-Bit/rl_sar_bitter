; Auto-generated. Do not edit!


(cl:in-package robot_msgs-msg)


;//! \htmlinclude LowlevelCmd.msg.html

(cl:defclass <LowlevelCmd> (roslisp-msg-protocol:ros-message)
  ((motorCmd
    :reader motorCmd
    :initarg :motorCmd
    :type (cl:vector robot_msgs-msg:LowlevelMotorCmd)
   :initform (cl:make-array 16 :element-type 'robot_msgs-msg:LowlevelMotorCmd :initial-element (cl:make-instance 'robot_msgs-msg:LowlevelMotorCmd))))
)

(cl:defclass LowlevelCmd (<LowlevelCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LowlevelCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LowlevelCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msgs-msg:<LowlevelCmd> is deprecated: use robot_msgs-msg:LowlevelCmd instead.")))

(cl:ensure-generic-function 'motorCmd-val :lambda-list '(m))
(cl:defmethod motorCmd-val ((m <LowlevelCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:motorCmd-val is deprecated.  Use robot_msgs-msg:motorCmd instead.")
  (motorCmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LowlevelCmd>) ostream)
  "Serializes a message object of type '<LowlevelCmd>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'motorCmd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LowlevelCmd>) istream)
  "Deserializes a message object of type '<LowlevelCmd>"
  (cl:setf (cl:slot-value msg 'motorCmd) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'motorCmd)))
    (cl:dotimes (i 16)
    (cl:setf (cl:aref vals i) (cl:make-instance 'robot_msgs-msg:LowlevelMotorCmd))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LowlevelCmd>)))
  "Returns string type for a message object of type '<LowlevelCmd>"
  "robot_msgs/LowlevelCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LowlevelCmd)))
  "Returns string type for a message object of type 'LowlevelCmd"
  "robot_msgs/LowlevelCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LowlevelCmd>)))
  "Returns md5sum for a message object of type '<LowlevelCmd>"
  "2b8ca0cf47ba441d44c5cb8cd95d8693")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LowlevelCmd)))
  "Returns md5sum for a message object of type 'LowlevelCmd"
  "2b8ca0cf47ba441d44c5cb8cd95d8693")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LowlevelCmd>)))
  "Returns full string definition for message of type '<LowlevelCmd>"
  (cl:format cl:nil "LowlevelMotorCmd[16] motorCmd~%================================================================================~%MSG: robot_msgs/LowlevelMotorCmd~%# uint8 mode           # motor target mode~%# float32 q            # motor target position~%# float32 dq           # motor target velocity~%# float32 tau          # motor target torque~%# float32 Kp           # motor spring stiffness coefficient~%# float32 Kd           # motor damper coefficient~%# uint32[3] reserve    # motor target torque~%~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%float32 Kvp~%float32 Kvi~%#uint8 rv #反转参数~%# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LowlevelCmd)))
  "Returns full string definition for message of type 'LowlevelCmd"
  (cl:format cl:nil "LowlevelMotorCmd[16] motorCmd~%================================================================================~%MSG: robot_msgs/LowlevelMotorCmd~%# uint8 mode           # motor target mode~%# float32 q            # motor target position~%# float32 dq           # motor target velocity~%# float32 tau          # motor target torque~%# float32 Kp           # motor spring stiffness coefficient~%# float32 Kd           # motor damper coefficient~%# uint32[3] reserve    # motor target torque~%~%# uint8 mode           # 电机当前模式~%uint8 id                # 电机ID~%float32 q            # 电机当前位置（弧度）~%float32 dq           # 电机当前速度（弧度/秒）~%float32 tau          # 当前输出扭矩（牛·米）~%#Kp ，Kd，反转参数reverse~%float32 Kp~%float32 Kd~%float32 Kvp~%float32 Kvi~%#uint8 rv #反转参数~%# int8 temperature     # 电机温度（由于温度传导缓慢，存在滞后现象）~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LowlevelCmd>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'motorCmd) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LowlevelCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'LowlevelCmd
    (cl:cons ':motorCmd (motorCmd msg))
))
