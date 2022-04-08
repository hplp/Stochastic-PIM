%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Code for the Sigma Delta
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [vOut,vInt,vError]= ASDM(x, schThrPerc, K, feedB, schOutLevel, timeStep, samples )

%-- System Parameters
schmittTriggerThreshold     = schThrPerc*schOutLevel; %- Switching threshold as a percentage

%IntegratorK                 = 3e-12; %- Integrator Constant (Capacitor value)

%%- Variables
lt        = samples;
vError    = zeros(1,lt); % Error function (Input-Feedback)
vFeedback = zeros(1,lt); % Feedback is just the output of the Schmitt Trigger
vInt      = zeros(1,lt); % Output of the integrator
vOut      = zeros(1,lt); % Output of the Modulator (Schmitt Trigger)

%%- Initial Conditions
vFeedback(1) = feedB*schOutLevel;

initCond = 0;
vInt(1)  = initCond;
for i=2:lt
  vError(i)    = x(i)-vFeedback(i-1);
  vInt(i)      = vInt(i-1) + (vError(i)*timeStep/K);
  vOut(i)      = schmittTrigger(vInt(i), vOut(i-1), schThrPerc, schOutLevel);
  vFeedback(i) = feedB*vOut(i);
end  


end
