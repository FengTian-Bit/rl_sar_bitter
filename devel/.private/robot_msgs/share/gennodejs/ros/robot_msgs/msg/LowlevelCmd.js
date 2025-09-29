// Auto-generated. Do not edit!

// (in-package robot_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let LowlevelMotorCmd = require('./LowlevelMotorCmd.js');

//-----------------------------------------------------------

class LowlevelCmd {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motorCmd = null;
    }
    else {
      if (initObj.hasOwnProperty('motorCmd')) {
        this.motorCmd = initObj.motorCmd
      }
      else {
        this.motorCmd = new Array(16).fill(new LowlevelMotorCmd());
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LowlevelCmd
    // Check that the constant length array field [motorCmd] has the right length
    if (obj.motorCmd.length !== 16) {
      throw new Error('Unable to serialize array field motorCmd - length must be 16')
    }
    // Serialize message field [motorCmd]
    obj.motorCmd.forEach((val) => {
      bufferOffset = LowlevelMotorCmd.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LowlevelCmd
    let len;
    let data = new LowlevelCmd(null);
    // Deserialize message field [motorCmd]
    len = 16;
    data.motorCmd = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.motorCmd[i] = LowlevelMotorCmd.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    return 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/LowlevelCmd';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2b8ca0cf47ba441d44c5cb8cd95d8693';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    LowlevelMotorCmd[16] motorCmd
    ================================================================================
    MSG: robot_msgs/LowlevelMotorCmd
    # uint8 mode           # motor target mode
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new LowlevelCmd(null);
    if (msg.motorCmd !== undefined) {
      resolved.motorCmd = new Array(16)
      for (let i = 0; i < resolved.motorCmd.length; ++i) {
        if (msg.motorCmd.length > i) {
          resolved.motorCmd[i] = LowlevelMotorCmd.Resolve(msg.motorCmd[i]);
        }
        else {
          resolved.motorCmd[i] = new LowlevelMotorCmd();
        }
      }
    }
    else {
      resolved.motorCmd = new Array(16).fill(new LowlevelMotorCmd())
    }

    return resolved;
    }
};

module.exports = LowlevelCmd;
