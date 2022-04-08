function out=schmittTrigger(xi,outim1,schmittTriggerThresholdPerc, schmittTriggerOutLevel)
   %out = schmittTriggerOutLevel*(sign_local(xi + sign_local(outim1)*schmittTriggerThreshold));
   %out = schmittTriggerOutLevel*(sign(xi + sign(outim1)*schmittTriggerThreshold));
   %out = -schmittTriggerOutLevel*sign(xi - outim1*schmittTriggerThreshold);
   %out = -schmittTriggerOutLevel*sign(xi - outim1*schmittTriggerThresholdPerc);
   out = schmittTriggerOutLevel*sign(xi + outim1*schmittTriggerThresholdPerc);
end
