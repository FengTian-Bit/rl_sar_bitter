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

class LowlevelMotorState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.id = null;
      this.q = null;
      this.dq = null;
      this.tau = null;
      this.Kp = null;
      this.Kd = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('q')) {
        this.q = initObj.q
      }
      else {
        this.q = 0.0;
      }
      if (initObj.hasOwnProperty('dq')) {
        this.dq = initObj.dq
      }
      else {
        this.dq = 0.0;
      }
      if (initObj.hasOwnProperty('tau')) {
        this.tau = initObj.tau
      }
      else {
        this.tau = 0.0;
      }
      if (initObj.hasOwnProperty('Kp')) {
        this.Kp = initObj.Kp
      }
      else {
        this.Kp = 0.0;
      }
      if (initObj.hasOwnProperty('Kd')) {
        this.Kd = initObj.Kd
      }
      else {
        this.Kd = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LowlevelMotorState
    // Serialize message field [stamp]
    bufferOffset = std_msgs.msg.Header.serialize(obj.stamp, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.uint8(obj.id, buffer, bufferOffset);
    // Serialize message field [q]
    bufferOffset = _serializer.float32(obj.q, buffer, bufferOffset);
    // Serialize message field [dq]
    bufferOffset = _serializer.float32(obj.dq, buffer, bufferOffset);
    // Serialize message field [tau]
    bufferOffset = _serializer.float32(obj.tau, buffer, bufferOffset);
    // Serialize message field [Kp]
    bufferOffset = _serializer.float32(obj.Kp, buffer, bufferOffset);
    // Serialize message field [Kd]
    bufferOffset = _serializer.float32(obj.Kd, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LowlevelMotorState
    let len;
    let data = new LowlevelMotorState(null);
    // Deserialize message field [stamp]
    data.stamp = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [q]
    data.q = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [dq]
    data.dq = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tau]
    data.tau = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Kp]
    data.Kp = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Kd]
    data.Kd = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.stamp);
    return length + 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/LowlevelMotorState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7be5bb1e36dfe9f0c461b081b3c9bca9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #时间戳
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LowlevelMotorState(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = std_msgs.msg.Header.Resolve(msg.stamp)
    }
    else {
      resolved.stamp = new std_msgs.msg.Header()
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.q !== undefined) {
      resolved.q = msg.q;
    }
    else {
      resolved.q = 0.0
    }

    if (msg.dq !== undefined) {
      resolved.dq = msg.dq;
    }
    else {
      resolved.dq = 0.0
    }

    if (msg.tau !== undefined) {
      resolved.tau = msg.tau;
    }
    else {
      resolved.tau = 0.0
    }

    if (msg.Kp !== undefined) {
      resolved.Kp = msg.Kp;
    }
    else {
      resolved.Kp = 0.0
    }

    if (msg.Kd !== undefined) {
      resolved.Kd = msg.Kd;
    }
    else {
      resolved.Kd = 0.0
    }

    return resolved;
    }
};

module.exports = LowlevelMotorState;
