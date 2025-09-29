// Auto-generated. Do not edit!

// (in-package robot_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LowlevelMotorState = require('./LowlevelMotorState.js');

//-----------------------------------------------------------

class LowlevelState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motorState = null;
    }
    else {
      if (initObj.hasOwnProperty('motorState')) {
        this.motorState = initObj.motorState
      }
      else {
        this.motorState = new Array(16).fill(new LowlevelMotorState());
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LowlevelState
    // Check that the constant length array field [motorState] has the right length
    if (obj.motorState.length !== 16) {
      throw new Error('Unable to serialize array field motorState - length must be 16')
    }
    // Serialize message field [motorState]
    obj.motorState.forEach((val) => {
      bufferOffset = LowlevelMotorState.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LowlevelState
    let len;
    let data = new LowlevelState(null);
    // Deserialize message field [motorState]
    len = 16;
    data.motorState = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.motorState[i] = LowlevelMotorState.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.motorState.forEach((val) => {
      length += LowlevelMotorState.getMessageSize(val);
    });
    return length;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/LowlevelState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '039d2d311ce4c771aaf577626734f296';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    LowlevelMotorState[16] motorState
    ================================================================================
    MSG: robot_msgs/LowlevelMotorState
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
    const resolved = new LowlevelState(null);
    if (msg.motorState !== undefined) {
      resolved.motorState = new Array(16)
      for (let i = 0; i < resolved.motorState.length; ++i) {
        if (msg.motorState.length > i) {
          resolved.motorState[i] = LowlevelMotorState.Resolve(msg.motorState[i]);
        }
        else {
          resolved.motorState[i] = new LowlevelMotorState();
        }
      }
    }
    else {
      resolved.motorState = new Array(16).fill(new LowlevelMotorState())
    }

    return resolved;
    }
};

module.exports = LowlevelState;
