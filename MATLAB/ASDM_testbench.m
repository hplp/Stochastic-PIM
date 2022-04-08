close all;
clear all;
clc;
%- Sigma-Delta parameters(Asynchronous Sigma Delta Modulator)
pxAmp       = 1;                      %- ASDM Feedback current
schOutLevel = 1;                      %- Output Voltage
schThrPerc  = 0.5;                    %- Comparator delta in percentage   
schThr      = schThrPerc*schOutLevel; %- Comparator delta
foc         = 25e3;                   %- Natural Frequency of ASDM
Toc         = 1/foc;                  %- Natural Period of ASDM 
K           = Toc*schOutLevel*pxAmp/(2*schThr); %- Capacitor
disp('INFO:')
disp('delta Nat-Freq. Nat-Period Capacitor')
display([num2str(schThr),'   ',num2str(foc),'     ',num2str(Toc),'   ',num2str(K)]);

timeStep = 1e-9; % "Sampling Frequeny" of 2.5 MHz
Fs=1/timeStep;
timeEnd  = 2e-3;  % PDM Stream length  
samples  = floor(timeEnd/timeStep);
time = (0:timeStep:timeEnd-timeStep);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%Generate Streams%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fi1    = 10e3;%- 1st tone frequency                           
px1    = ones(1, samples).*1; % input to ASDM
[xStream1, vInt, vError]=ASDM(px1, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%PLOTTING FIGURES%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
subplot(2,1,1)
hold on 
grid on
xlim([0, 1e-3])
ylim([-1.25,1.25])
plot(time,px1)
title("Input signal")
hold off
subplot(2,1,2)
hold on 
grid on
xlim([0, 1e-3])
plot(time,xStream1)
title("Generated ASDM Stream")
ylim([-1.25,1.25])
hold off