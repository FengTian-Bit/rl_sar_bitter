// Auto-generated. Do not edit!

// (in-package robot_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class LowlevelMotorCmd {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.q = null;
      this.dq = null;
      this.tau = null;
      this.Kp = null;
      this.Kd = null;
      this.Kvp = null;
      this.Kvi = null;
    }
    else {
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
      if (initObj.hasOwnProperty('Kvp')) {
        this.Kvp = initObj.Kvp
      }
      else {
        this.Kvp = 0.0;
      }
      if (initObj.hasOwnProperty('Kvi')) {
        this.Kvi = initObj.Kvi
      }
      else {
        this.Kvi = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type LowlevelMotorCmd
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
    // Serialize message field [Kvp]
    bufferOffset = _serializer.float32(obj.Kvp, buffer, bufferOffset);
    // Serialize message field [Kvi]
    bufferOffset = _serializer.float32(obj.Kvi, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type LowlevelMotorCmd
    let len;
    let data = new LowlevelMotorCmd(null);
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
    // Deserialize message field [Kvp]
    data.Kvp = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Kvi]
    data.Kvi = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/LowlevelMotorCmd';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '287e30467db2eeba6fc4bc80506a1206';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new LowlevelMotorCmd(null);
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

    if (msg.Kvp !== undefined) {
      resolved.Kvp = msg.Kvp;
    }
    else {
      resolved.Kvp = 0.0
    }

    if (msg.Kvi !== undefined) {
      resolved.Kvi = msg.Kvi;
    }
    else {
      resolved.Kvi = 0.0
    }

    return resolved;
    }
};

module.exports = LowlevelMotorCmd;
