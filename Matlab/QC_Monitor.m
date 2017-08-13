%% Create plots
run('create_graphs');

%% Start Serial Comm
delete(instrfindall);
delete(instrfindall);
port = serial('/dev/cu.usbmodem1413','BaudRate',115200,'DataBits',8, 'Byteorder', 'littleEndian');
fopen(port);
fclose(port);
fopen(port);
flag=0;
gyro_data = zeros(3,1);
input_data = zeros(4,1);
motor_output = zeros(4,1);
count=1001;
array = [(0), (0), (0), (0), (0)];

%initialize plot data
plot1_dataX = 0;
plot1_dataY = 0;
plot2_data = 0;
plot3_data = 0;
plot4_data = 0;
plotHandle = plot(axesHandle, 4100-plot1_dataX, plot1_dataY, '+', 'color', [0 1 0]);
plotHandle2 = plot(axesHandle2, plot2_data, count, 'color', [0 0 1]);
plotHandle3 = plot(axesHandle3, plot3_data, 0, '-*', 'color', [1 0 0]);
plotHandle4 = plot(axesHandle4, plot4_data, 0, '-*', 'color', [1 0 1]);
ylim(axesHandle3, [0 200]);
ylim(axesHandle4, [0 50]);
while flag==0
    tic;
    
    %Get data from quadcopter
    [gyro_data, input_data] = quad_recv(port);
    
    %use input data for PID tuning
    Kp2 = 130 - 0.0325*input_data(1);
    Kp2 = round(Kp2, 0);
    if Kp < 0
        Kp = 0;
    end
    Kd = 30 - 0.0075*input_data(2);
    Kd = round(Kd, 0);
    if Kd < 0
        Kd = 0;
    end
    
    des_roll = 0;
    des_pitch = 0;
    des_yaw = 0;
    
    Kp = 103;
    
    %motor outputs
    motor_output(3) = 450 ...  
        - Kp*(des_roll - gyro_data(1)) -Kd*(-gyro_data(4))...
        + Kp*(des_pitch - gyro_data(2)) +Kd*(-gyro_data(5))...
        +10*(gyro_data(6));
    
    motor_output(2) = 450 ...
        - Kp*(des_roll - gyro_data(1)) -Kd*(-gyro_data(4))...
        - Kp*(des_pitch - gyro_data(2)) -Kd*(-gyro_data(5))...
        -10*(gyro_data(6));
    
    motor_output(1) = 450 ...
        + Kp*(des_roll - gyro_data(1)) +Kd*(-gyro_data(4))...
        - Kp*(des_pitch - gyro_data(2)) -Kd*(-gyro_data(5))...
        +10*(gyro_data(6));
    motor_output(4) = 450 ...
        + Kp*(des_roll - gyro_data(1)) +Kd*(-gyro_data(4))...
        + Kp*(des_pitch - gyro_data(2)) +Kd*(-gyro_data(5))...
        -10*(gyro_data(6));
%     motor_output(1) = 460 + 100*sign(sin(0.05*count));
%     motor_output(2) = 0;
%     motor_output(3) = 0;
%     motor_output(4) = 0;

    
    motor_output(1) = motor_output(1) - Kp2*sin(gyro_data(1)) + ... 
        Kp2*sin(gyro_data(2));
    motor_output(2) = motor_output(2) + Kp2*sin(gyro_data(1)) + ... 
        Kp2*sin(gyro_data(2));
    motor_output(3) = motor_output(3) + Kp2*sin(gyro_data(1)) - ... 
        Kp2*sin(gyro_data(2));
    motor_output(4) = motor_output(4) - Kp2*sin(gyro_data(1)) - ... 
        Kp2*sin(gyro_data(2));

    %update plots
    plot1_dataY(count) = input_data(4);
    plot1_dataX(count) = input_data(3);
    plot2_data(count) = gyro_data(6);
    plot3_data(count) = Kp2;
    plot4_data(count) = Kd;
    
%     set(plotHandle,'XData',4100-plot1_dataX(count-10:count),'YData',plot1_dataY(count-10:count));
    set(plotHandle2,'YData',plot2_data(count-200:count),'XData', (count-200):count);
    set(plotHandle3,'YData', plot3_data((count-10):count), 'Xdata', [1 1 1 1 1 1 1 1 1 1 1]);
    set(plotHandle4,'YData', plot4_data((count-10):count), 'Xdata', [1 1 1 1 1 1 1 1 1 1 1]);

    xlim(axesHandle2, [(count-200) (count+50)]);
    count = count +1;
  
    %Send to quadcopter
    quad_send(port, motor_output);
    pause(0.001)
    toc;

end

