%%

port = "/dev/ttyACM0"
buffersize = 3000;
data = plotArduino(port,buffersize)

fileID = fopen(['expdata_',datestr(now,'yyyy11dd_HHMMSS'),'.csv'],'w');

fprintf(fileID,"time(ms),enconder(steps),inputSignal(8bits),controlSignal\n");

dataSize = size(data);
for i = 1:dataSize(1)
    fprintf(fileID,"%d,%d,%d,%d\n",data(i,1),data(i,2),data(i,3),data(i,4));
end

fclose(fileID);
