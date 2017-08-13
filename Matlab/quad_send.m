function quad_send(port, motor_output)
%QUAD_SEND Summary of this function goes here
%   Detailed explanation goes here
    out_array = [1, motor_output(1), motor_output(2), motor_output(3), motor_output(4)];
    
    %Send write request to quadcopter
    fwrite(port, out_array, 'uint16');
    
end

