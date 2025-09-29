; Auto-generated. Do not edit!


(cl:in-package robot_msgs-msg)


;//! \htmlinclude Observation.msg.html

(cl:defclass <Observation> (roslisp-msg-protocol:ros-message)
  ((ang_vel
    :reader ang_vel
    :initarg :ang_vel
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (gravity_vec
    :reader gravity_vec
    :initarg :gravity_vec
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (commands
    :reader commands
    :initarg :commands
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (dof_pos
    :reader dof_pos
    :initarg :dof_pos
    :type (cl:vector cl:float)
   :initform (cl:make-array 16 :element-type 'cl:float :initial-element 0.0))
   (dof_vel
    :reader dof_vel
    :initarg :dof_vel
    :type (cl:vector cl:float)
   :initform (cl:make-array 16 :element-type 'cl:float :initial-element 0.0))
   (actions
    :reader actions
    :initarg :actions
    :type (cl:vector cl:float)
   :initform (cl:make-array 16 :element-type 'cl:float :initial-element 0.0))
   (obs
    :reader obs
    :initarg :obs
    :type (cl:vector cl:float)
   :initform (cl:make-array 57 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass Observation (<Observation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Observation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Observation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_msgs-msg:<Observation> is deprecated: use robot_msgs-msg:Observation instead.")))

(cl:ensure-generic-function 'ang_vel-val :lambda-list '(m))
(cl:defmethod ang_vel-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:ang_vel-val is deprecated.  Use robot_msgs-msg:ang_vel instead.")
  (ang_vel m))

(cl:ensure-generic-function 'gravity_vec-val :lambda-list '(m))
(cl:defmethod gravity_vec-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:gravity_vec-val is deprecated.  Use robot_msgs-msg:gravity_vec instead.")
  (gravity_vec m))

(cl:ensure-generic-function 'commands-val :lambda-list '(m))
(cl:defmethod commands-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:commands-val is deprecated.  Use robot_msgs-msg:commands instead.")
  (commands m))

(cl:ensure-generic-function 'dof_pos-val :lambda-list '(m))
(cl:defmethod dof_pos-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:dof_pos-val is deprecated.  Use robot_msgs-msg:dof_pos instead.")
  (dof_pos m))

(cl:ensure-generic-function 'dof_vel-val :lambda-list '(m))
(cl:defmethod dof_vel-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:dof_vel-val is deprecated.  Use robot_msgs-msg:dof_vel instead.")
  (dof_vel m))

(cl:ensure-generic-function 'actions-val :lambda-list '(m))
(cl:defmethod actions-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:actions-val is deprecated.  Use robot_msgs-msg:actions instead.")
  (actions m))

(cl:ensure-generic-function 'obs-val :lambda-list '(m))
(cl:defmethod obs-val ((m <Observation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_msgs-msg:obs-val is deprecated.  Use robot_msgs-msg:obs instead.")
  (obs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Observation>) ostream)
  "Serializes a message object of type '<Observation>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'ang_vel))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'gravity_vec))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'commands))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'dof_pos))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'dof_vel))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'actions))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'obs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Observation>) istream)
  "Deserializes a message object of type '<Observation>"
  (cl:setf (cl:slot-value msg 'ang_vel) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'ang_vel)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'gravity_vec) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'gravity_vec)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'commands) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'commands)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'dof_pos) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'dof_pos)))
    (cl:dotimes (i 16)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'dof_vel) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'dof_vel)))
    (cl:dotimes (i 16)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'actions) (cl:make-array 16))
  (cl:let ((vals (cl:slot-value msg 'actions)))
    (cl:dotimes (i 16)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'obs) (cl:make-array 57))
  (cl:let ((vals (cl:slot-value msg 'obs)))
    (cl:dotimes (i 57)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Observation>)))
  "Returns string type for a message object of type '<Observation>"
  "robot_msgs/Observation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Observation)))
  "Returns string type for a message object of type 'Observation"
  "robot_msgs/Observation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Observation>)))
  "Returns md5sum for a message object of type '<Observation>"
  "1cf74daf5018ef55d2264614972f54c9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Observation)))
  "Returns md5sum for a message object of type 'Observation"
  "1cf74daf5018ef55d2264614972f54c9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Observation>)))
  "Returns full string definition for message of type '<Observation>"
  (cl:format cl:nil "#可单取出来~%float32[3] ang_vel   # 角速度 wx, wy, wz~%float32[3] gravity_vec  ~%float32[3] commands~%float32[16] dof_pos~%float32[16] dof_vel~%float32[16] actions~%#总观测量~%float32[57] obs~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Observation)))
  "Returns full string definition for message of type 'Observation"
  (cl:format cl:nil "#可单取出来~%float32[3] ang_vel   # 角速度 wx, wy, wz~%float32[3] gravity_vec  ~%float32[3] commands~%float32[16] dof_pos~%float32[16] dof_vel~%float32[16] actions~%#总观测量~%float32[57] obs~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Observation>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'ang_vel) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'gravity_vec) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'commands) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'dof_pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'dof_vel) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'actions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'obs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Observation>))
  "Converts a ROS message object to a list"
  (cl:list 'Observation
    (cl:cons ':ang_vel (ang_vel msg))
    (cl:cons ':gravity_vec (gravity_vec msg))
    (cl:cons ':commands (commands msg))
    (cl:cons ':dof_pos (dof_pos msg))
    (cl:cons ':dof_vel (dof_vel msg))
    (cl:cons ':actions (actions msg))
    (cl:cons ':obs (obs msg))
))
