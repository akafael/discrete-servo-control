%%

% Get path from current file and generate absolute path
file_path = fileparts(mfilename('fullpath'))
data_path = strcat(file_path,"/../../data/")

% Read Exp Data
filename = strcat(data_path,"expdata_20201124_220716.csv")
fileID = fopen(filename,'r')
fgets(fileID)
data = transpose(fscanf(fileID,"%d,%d,%d",[3 Inf]))

% Split data into column vectors
t = data(:,1)
y = data(:,2)
u = data(:,3)

% Find Period
Ts = mean(diff(data(:,1)))/1000

% Find coefficients
k = 1:2000;
A = [-y(k+1) -y(k) u(k+1) u(k)];
coeff = inv(A'*A)*A'*y(k+2)

% Symbolic Discrete Transfer Function
num = vpa(poly2sym(coeff(3:4)',z),4);
den = vpa(poly2sym([1 coeff(1:2)'],z),4);
sGz = num/den

%  Discrete Transfer Function
Gz = tf(coeff(3:4)',[1 coeff(1:2)'],Ts)
