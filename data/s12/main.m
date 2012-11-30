%function main()
% MAIN 主函数
% 产生想定12的测试数据
%共有5列：[t, x, y, v, seta]
% 分别代表时间、x轴位置，y轴位置，速度大小，速度方向

tic;
clc;
samplePoint=86401;
initial1=[0,0,20,0];
sampleInterval=1; %采样间隔1s
coordinate1=zeros(4,samplePoint); %存储目标1各个采样时刻的状态值，列存储
idxTime1=zeros(1,samplePoint); %目标1时间序号
coordinate1(:,1)=initial1;
%%目标1的运动
%采样间隔是1s，所以24h要采样86400次
for idxSample=2:samplePoint  %匀加速运动
    idxTime1(idxSample)=idxTime1(idxSample-1)+sampleInterval;
    coordinate1(1,idxSample) = coordinate1(1,idxSample-1) + ...
                coordinate1(3,idxSample-1)*cos(coordinate1(4,idxSample-1))*sampleInterval;
    coordinate1(2,idxSample) = coordinate1(2,idxSample-1);    
    coordinate1(3,idxSample) = coordinate1(3,idxSample-1);
    coordinate1(4,idxSample) = coordinate1(4,idxSample-1);
end

coordinate1(2:5,:)=coordinate1;
%把两个目标的数据合在一起
coordinate1(1,:)=idxTime1;
dlmwrite('data.txt', coordinate1', 'delimiter', '\t', 'newline', 'pc','precision',  '%.2f');
toc;