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

class Observation {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ang_vel = null;
      this.gravity_vec = null;
      this.commands = null;
      this.dof_pos = null;
      this.dof_vel = null;
      this.actions = null;
      this.obs = null;
    }
    else {
      if (initObj.hasOwnProperty('ang_vel')) {
        this.ang_vel = initObj.ang_vel
      }
      else {
        this.ang_vel = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('gravity_vec')) {
        this.gravity_vec = initObj.gravity_vec
      }
      else {
        this.gravity_vec = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('commands')) {
        this.commands = initObj.commands
      }
      else {
        this.commands = new Array(3).fill(0);
      }
      if (initObj.hasOwnProperty('dof_pos')) {
        this.dof_pos = initObj.dof_pos
      }
      else {
        this.dof_pos = new Array(16).fill(0);
      }
      if (initObj.hasOwnProperty('dof_vel')) {
        this.dof_vel = initObj.dof_vel
      }
      else {
        this.dof_vel = new Array(16).fill(0);
      }
      if (initObj.hasOwnProperty('actions')) {
        this.actions = initObj.actions
      }
      else {
        this.actions = new Array(16).fill(0);
      }
      if (initObj.hasOwnProperty('obs')) {
        this.obs = initObj.obs
      }
      else {
        this.obs = new Array(57).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Observation
    // Check that the constant length array field [ang_vel] has the right length
    if (obj.ang_vel.length !== 3) {
      throw new Error('Unable to serialize array field ang_vel - length must be 3')
    }
    // Serialize message field [ang_vel]
    bufferOffset = _arraySerializer.float32(obj.ang_vel, buffer, bufferOffset, 3);
    // Check that the constant length array field [gravity_vec] has the right length
    if (obj.gravity_vec.length !== 3) {
      throw new Error('Unable to serialize array field gravity_vec - length must be 3')
    }
    // Serialize message field [gravity_vec]
    bufferOffset = _arraySerializer.float32(obj.gravity_vec, buffer, bufferOffset, 3);
    // Check that the constant length array field [commands] has the right length
    if (obj.commands.length !== 3) {
      throw new Error('Unable to serialize array field commands - length must be 3')
    }
    // Serialize message field [commands]
    bufferOffset = _arraySerializer.float32(obj.commands, buffer, bufferOffset, 3);
    // Check that the constant length array field [dof_pos] has the right length
    if (obj.dof_pos.length !== 16) {
      throw new Error('Unable to serialize array field dof_pos - length must be 16')
    }
    // Serialize message field [dof_pos]
    bufferOffset = _arraySerializer.float32(obj.dof_pos, buffer, bufferOffset, 16);
    // Check that the constant length array field [dof_vel] has the right length
    if (obj.dof_vel.length !== 16) {
      throw new Error('Unable to serialize array field dof_vel - length must be 16')
    }
    // Serialize message field [dof_vel]
    bufferOffset = _arraySerializer.float32(obj.dof_vel, buffer, bufferOffset, 16);
    // Check that the constant length array field [actions] has the right length
    if (obj.actions.length !== 16) {
      throw new Error('Unable to serialize array field actions - length must be 16')
    }
    // Serialize message field [actions]
    bufferOffset = _arraySerializer.float32(obj.actions, buffer, bufferOffset, 16);
    // Check that the constant length array field [obs] has the right length
    if (obj.obs.length !== 57) {
      throw new Error('Unable to serialize array field obs - length must be 57')
    }
    // Serialize message field [obs]
    bufferOffset = _arraySerializer.float32(obj.obs, buffer, bufferOffset, 57);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Observation
    let len;
    let data = new Observation(null);
    // Deserialize message field [ang_vel]
    data.ang_vel = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [gravity_vec]
    data.gravity_vec = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [commands]
    data.commands = _arrayDeserializer.float32(buffer, bufferOffset, 3)
    // Deserialize message field [dof_pos]
    data.dof_pos = _arrayDeserializer.float32(buffer, bufferOffset, 16)
    // Deserialize message field [dof_vel]
    data.dof_vel = _arrayDeserializer.float32(buffer, bufferOffset, 16)
    // Deserialize message field [actions]
    data.actions = _arrayDeserializer.float32(buffer, bufferOffset, 16)
    // Deserialize message field [obs]
    data.obs = _arrayDeserializer.float32(buffer, bufferOffset, 57)
    return data;
  }

  static getMessageSize(object) {
    return 456;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robot_msgs/Observation';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1cf74daf5018ef55d2264614972f54c9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #可单取出来
    float32[3] ang_vel   # 角速度 wx, wy, wz
    float32[3] gravity_vec  
    float32[3] commands
    float32[16] dof_pos
    float32[16] dof_vel
    float32[16] actions
    #总观测量
    float32[57] obs
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Observation(null);
    if (msg.ang_vel !== undefined) {
      resolved.ang_vel = msg.ang_vel;
    }
    else {
      resolved.ang_vel = new Array(3).fill(0)
    }

    if (msg.gravity_vec !== undefined) {
      resolved.gravity_vec = msg.gravity_vec;
    }
    else {
      resolved.gravity_vec = new Array(3).fill(0)
    }

    if (msg.commands !== undefined) {
      resolved.commands = msg.commands;
    }
    else {
      resolved.commands = new Array(3).fill(0)
    }

    if (msg.dof_pos !== undefined) {
      resolved.dof_pos = msg.dof_pos;
    }
    else {
      resolved.dof_pos = new Array(16).fill(0)
    }

    if (msg.dof_vel !== undefined) {
      resolved.dof_vel = msg.dof_vel;
    }
    else {
      resolved.dof_vel = new Array(16).fill(0)
    }

    if (msg.actions !== undefined) {
      resolved.actions = msg.actions;
    }
    else {
      resolved.actions = new Array(16).fill(0)
    }

    if (msg.obs !== undefined) {
      resolved.obs = msg.obs;
    }
    else {
      resolved.obs = new Array(57).fill(0)
    }

    return resolved;
    }
};

module.exports = Observation;
