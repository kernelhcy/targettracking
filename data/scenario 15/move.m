function coordinateCartesian=move(coordinateCartesian,sampleIntervalValue)
% MOVE ����ֱ���˶�
sampleInterval=sampleIntervalValue;
if(size(coordinateCartesian,2)<41)
    error('out ot range');
end
for idxSample=2:41 %���������0.5s������20sҪ����40��
    coordinateCartesian(1,idxSample) = ...
    coordinateCartesian(1,idxSample-1) + coordinateCartesian(3,idxSample-1)*cos(coordinateCartesian(4,idxSample-1))*sampleInterval;
    coordinateCartesian(2,idxSample) = ...
    coordinateCartesian(2,idxSample-1) + coordinateCartesian(3,idxSample-1)*sin(coordinateCartesian(4,idxSample-1))*sampleInterval;
    coordinateCartesian(3,idxSample) = coordinateCartesian(3,idxSample-1);
    coordinateCartesian(4,idxSample) = coordinateCartesian(4,idxSample-1);
end



