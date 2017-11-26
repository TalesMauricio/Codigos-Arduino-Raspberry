

% FIR filter designed with
% http://t-filter.appspot.com
%
% sampling frequency: 10 Hz
%
%* 0 Hz - 0.1 Hz
%  gain = 1
%  desired ripple = 5 dB
%  actual ripple = 4.169952965424239 dB
%
%* 0.2 Hz - 5 Hz
%  gain = 0
%  desired attenuation = -40 dB
%  actual attenuation = -40.01202996688569 dB


close all
clc
format long

h = [ -0.005518034512137216
-0.0010814112228576655
-0.0011715558702631759
-0.0012552710889628567
-0.0013308334353300155
-0.0013967720783365626
-0.0014511208454426885
-0.001491791836425203
-0.0015160592026807025
-0.0015226185203396953
-0.0015085197577844182
-0.0014722040762444061
-0.0014123695184736764
-0.0013265619010405913
-0.001212508065275172
-0.0010684583872677576
-0.0008921788103756073
-0.0006825463717743312
-0.0004387799868456526
-0.00015906757682741153
0.00015944877611416515
0.0005166947881782396
0.0009101913461917016
0.0013468674321911376
0.001821182269630084
0.0023359211799397657
0.00289002069821335
0.0034830014583876875
0.004114140043280624
0.004781943608556381
0.0054864780888605955
0.006223389801475368
0.006993510283712941
0.007793402699866823
0.008619934041613231
0.009471306960631379
0.010344519347966881
0.011235727852504136
0.012141564768453447
0.013058843694340594
0.013983343005131637
0.01491091018305646
0.015837908548011613
0.016759571697504576
0.017671066542843852
0.01856971665908746
0.019449862739335456
0.02030794752010053
0.021139483236666628
0.021940318316778305
0.022706408113284997
0.02343154310727671
0.024122772922803227
0.02475204631049552
0.025343313056079852
0.02588187171722733
0.026360455187262755
0.026778585734640446
0.027136597091489186
0.02743366193275918
0.02766770009312151
0.02783708048802205
0.0279393249242809
0.02797338964909767
0.0279393249242809
0.02783708048802205
0.02766770009312151
0.02743366193275918
0.027136597091489186
0.026778585734640446
0.026360455187262755
0.02588187171722733
0.025343313056079852
0.02475204631049552
0.024122772922803227
0.02343154310727671
0.022706408113284997
0.021940318316778305
0.021139483236666628
0.02030794752010053
0.019449862739335456
0.01856971665908746
0.017671066542843852
0.016759571697504576
0.015837908548011613
0.01491091018305646
0.013983343005131637
0.013058843694340594
0.012141564768453447
0.011235727852504136
0.010344519347966881
0.009471306960631379
0.008619934041613231
0.007793402699866823
0.006993510283712941
0.006223389801475368
0.0054864780888605955
0.004781943608556381
0.004114140043280624
0.0034830014583876875
0.00289002069821335
0.0023359211799397657
0.001821182269630084
0.0013468674321911376
0.0009101913461917016
0.0005166947881782396
0.00015944877611416515
-0.00015906757682741153
-0.0004387799868456526
-0.0006825463717743312
-0.0008921788103756073
-0.0010684583872677576
-0.001212508065275172
-0.0013265619010405913
-0.0014123695184736764
-0.0014722040762444061
-0.0015085197577844182
-0.0015226185203396953
-0.0015160592026807025
-0.001491791836425203
-0.0014511208454426885
-0.0013967720783365626
-0.0013308334353300155
-0.0012552710889628567
-0.0011715558702631759
-0.0010814112228576655
-0.005518034512137216
];

s = sum(h);
freqz(h/s,1,500)
h = floor(h*(2^8-1)/max(h))
figure
divisor = sum(h)
freqz(h/divisor,1,500)

fs = 10;
tf = 60;
N = tf*fs;
t = 0:1/fs:tf;

x = (0:N)*10/N + 2*rand(1,N+1)-1 + 2*sin(2*pi*0.2*t);
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
