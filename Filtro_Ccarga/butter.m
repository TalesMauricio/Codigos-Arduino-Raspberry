% 
% FIR filter designed with
% http://t-filter.appspot.com
% 
% sampling frequency: 10 Hz
% 
% fixed point precision: 16 bits
% 
% * 0 Hz - 0.5 Hz
%   gain = 1
%   desired ripple = 2 dB
%   actual ripple = n/a
% 
% * 1.5 Hz - 5 Hz
%   desired attenuation = -60 dB
%

close all
clc
format long

h = [ -0.0022870940699551154
-0.0028182630572891193
-0.0008793923902916939
0.006999433263281532
0.02349496572331729
0.04937024067048178
0.08235272220740557
0.11705644222569238
0.1462144437689986
0.1629016754277729
0.1629016754277729
0.1462144437689986
0.11705644222569238
0.08235272220740557
0.04937024067048178
0.02349496572331729
0.006999433263281532
-0.0008793923902916939
-0.0028182630572891193
-0.0022870940699551154
];

s = sum(h);
freqz(h/s,1,500)
h = ceil(h*(2^16-1)/max(h))
figure
s = sum(h)
freqz(h/s,1,500)

fs = 10;
tf = 5;
N = tf*fs;
t = 0:1/fs:tf;

x = (0:N)*10/N + 2*rand(1,N+1)-1;
y = zeros(N+1,1);

for n = 1:N+1
    for k = 0:length(h)-1
        if (n-k)>0
            y(n) = y(n) + x(n-k)*h(k+1);
        end
    end
end

figure
y = y/sum(h)
erro = x(N)-y(N)

plot(t,x,'k')
hold on
plot(t,y,'b')