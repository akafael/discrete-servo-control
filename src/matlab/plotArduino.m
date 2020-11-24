%% Arduino Test
function x = plotArduino(port,buffersize)

    % Connect to Arduino
    delete(instrfind({'Port'},{port}));
    serialPort = serial(port);
    serialPort.BaudRate = 9600; % High BaudRate cause buffer skipping
    fopen(serialPort);

    x = zeros(buffersize,3);
    i = 1;

    while ((~isempty(serialPort)) && strcmp(serialPort.Status,'open') && i <= buffersize)
        % Read Data
        str = fgetl(serialPort);
        str = strsplit(str, ',')

        x(i,1) = str2double(str{1});
        x(i,2) = str2double(str{2});
        x(i,3) = str2double(str{3});

        % Update Index
        i = i+1;
    end
 end
