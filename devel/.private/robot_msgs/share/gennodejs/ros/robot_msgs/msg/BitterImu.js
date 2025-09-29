// Auto-generated. Do not edit!

// (in-package robot_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class BitterImu {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.quat = null;
      this.angular_vel_local = null;
      this.linear_acc_local = null;
      this.orientation_cov = null;
      this.angular_vel_cov = null;
      this.linear_acc_cov = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('quat')) {
        this.quat = initObj.quat
      }
      else {
        this.quat = new Array(4).fill(0);
      }
      if (initObj.hasOwnProperty('angular_vel_local')) {
        this.angular_vel_local = initObj.angular_vel_local
      }
      else {
        this.angular_vel_local = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('linear_acc_local')) {
        this.linear_acc_local = initObj.linear_acc_local
      }
      else {
        this.linear_acc_local = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('orientation_cov')) {
        this.orientation_cov = initObj.orientation_cov
      }
      else {
        this.orientation_cov = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('angular_vel_cov')) {
        this.angular_vel_cov = initObj.angular_vel_cov
      }
      else {
        this.angular_vel_cov = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('linear_acc_cov')) {
        this.linear_acc_cov = initObj.linear_acc_cov
      }
      else {
        this.linear_acc_cov = new Array(9).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BitterImu
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Check that the constant length array field [quat] has the right length
    if (obj.quat.length !== 4) {
      throw new Error('Unable to serialize array field quat - length must be 4')
    }
    // Serialize message field [quat]
    bufferOffset = _arraySerializer.float64(obj.quat, buffer, bufferOffset, 4);
    // Check that the constant length array field [angular_vel_local] has the right length
    if (obj.angular_vel_local.length !== 3) {
      throw new Error('Unable to serialize array field angular_vel_local - length must be 3')
    }
    // Serialize message field [angular_vel_local]
    bufferOffset = _arraySerializer.float64(obj.angular_vel_local, buffer, bufferOffset, 3);
    // Check that the constant length array field [linear_acc_local] has the right length
    if (obj.linear_acc_local.length !== 3) {
      throw new Error('Unable to serialize array field linear_acc_local - length must be 3')
    }
    // Serialize message field [linear_acc_local]
    bufferOffset = _arraySerializer.float64(obj.linear_acc_local, buffer, bufferOffset, 3);
    // Check that the constant length array field [orientation_cov] has the right length
    if (obj.orientation_cov.length !== 9) {
      throw new Error('Unable to serialize array field orientation_cov - length must be 9')
    }
    // Serialize message field [orientation_cov]
    bufferOffset = _arraySerializer.float64(obj.orientation_cov, buffer, bufferOffset, 9);
    // Check that the constant length array field [angular_vel_cov] has the right length
    if (obj.angular_vel_cov.length !== 9) {
      throw new Error('Unable to serialize array field angular_vel_cov - length must be 9')
    }
    // Serialize message field [angular_vel_cov]
    bufferOffset = _arraySerializer.float64(obj.angular_vel_cov, buffer, bufferOffset, 9);
    // Check that the constant length array field [linear_acc_cov] has the right length
    if (obj.linear_acc_cov.length !== 9) {
      throw new Error('Unable to serialize array field linear_acc_cov - length must be 9')
    }
    // Serialize message field [linear_acc_cov]
    bufferOffset = _arraySerializer.float64(obj.linear_acc_cov, buffer, bufferOffset, 9);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BitterImu
    let len;
    let data = new BitterImu(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [quat]
    data.quat = _arrayDeserializer.float64(buffer, bufferOffset, 4)
    // Deserialize message field [angular_vel_local]
    data.angular_vel_local = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [linear_acc_local]
    data.linear_acc_local = _arrayDeserializer.float64(buffer, bufferOffset, 3)
    // Deserialize message field [orientation_cov]
    data.orientation_cov = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [angular_vel_cov]
    data.angular_vel_cov = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [linear_acc_cov]
    data.linear_acc_cov = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 296;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/BitterImu';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0f4e8b4bfb725baef44f23478818d1c0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # 自定义IMU消息格式
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BitterImu(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.quat !== undefined) {
      resolved.quat = msg.quat;
    }
    else {
      resolved.quat = new Array(4).fill(0)
    }

    if (msg.angular_vel_local !== undefined) {
      resolved.angular_vel_local = msg.angular_vel_local;
    }
    else {
      resolved.angular_vel_local = new Array(3).fill(0)
    }

    if (msg.linear_acc_local !== undefined) {
      resolved.linear_acc_local = msg.linear_acc_local;
    }
    else {
      resolved.linear_acc_local = new Array(3).fill(0)
    }

    if (msg.orientation_cov !== undefined) {
      resolved.orientation_cov = msg.orientation_cov;
    }
    else {
      resolved.orientation_cov = new Array(9).fill(0)
    }

    if (msg.angular_vel_cov !== undefined) {
      resolved.angular_vel_cov = msg.angular_vel_cov;
    }
    else {
      resolved.angular_vel_cov = new Array(9).fill(0)
    }

    if (msg.linear_acc_cov !== undefined) {
      resolved.linear_acc_cov = msg.linear_acc_cov;
    }
    else {
      resolved.linear_acc_cov = new Array(9).fill(0)
    }

    return resolved;
    }
};

module.exports = BitterImu;
