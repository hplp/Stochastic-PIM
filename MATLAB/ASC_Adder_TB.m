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
px1    = 0.7.*ones([1,samples]);% input 1 to ASDM
px2    = 0.11.*ones([1,samples]);% input 2 to ASDM
px3    = 0.3.*ones([1,samples]);% input 3 to ASDM
px4    = 0.7.*ones([1,samples]);% input 3 to ASDM
[xStream1, vInt1, vError1]=ASDM(px1, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );
[xStream2, vInt2, vError2]=ASDM(px2, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );
[xStream3, vInt3, vError3]=ASDM(px3, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );
[xStream4, vInt4, vError4]=ASDM(px4, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );
%%%%%%%%%%%%%%%%%%%%%%%%%%INPUT TO ADDER MODULE%%%%%%%%%%%%%%%%%%%%%%%%%%%%
xStream = [xStream1;xStream2;xStream3;xStream4];
[adder_stream, vInt3, vError3] = ASC_adder_v2(xStream,4, schThrPerc, K, 2*pxAmp, schOutLevel, timeStep, samples );


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%PLOTTING FIGURES%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
subplot(3,1,1)
hold on 
grid on
xlim([0, 1e-3])
ylim([-1.25,1.25])
plot(time,xStream1,'DisplayName','input stream#1')
% plot(time,xStream2,'DisplayName','input stream#2')
title("Input streams to adder")
hold off
subplot(3,1,2)
hold on 
grid on
xlim([0, 1e-3])
ylim([-1.25,1.25])
% plot(time,xStream1,'DisplayName','input stream#1')
plot(time,xStream2,'DisplayName','input stream#2')
title("Input streams to adder")
hold off
subplot(3,1,3)
hold on 
grid on
xlim([0, 1e-3])
plot(time,adder_stream)
title("Generated Stream from ASC adder")
ylim([-1.25,1.25])
hold off