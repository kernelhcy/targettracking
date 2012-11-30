% function main()
% MAIN 主函数
% 16个集群（各含三个目标）平行机动，无杂波，各目标成三角型
%共有六列：[t, x, y, v, seta, No]
% 分别代表时间，x轴位置，y轴位置，速度大小，速度方向，集群编号
tic;
clc;
clear;
%coordinateCartesian_1代表第一个集群，coordinateCartesian_2代表第二个集群，
initialCartesian_1{1}=[0,0,10,0,1]'; 
initialCartesian_1{2}=[-10,-10,10,0,1]'; 
initialCartesian_1{3}=[-10,10,10,0,1]'; 

initialCartesian_2{1}=[0,50,10,0,2]'; 
initialCartesian_2{2}=[-10,40,10,0,2]'; 
initialCartesian_2{3}=[-10,60,10,0,2]'; 

initialCartesian_3{1}=[0,100,10,0,3]'; 
initialCartesian_3{2}=[-10,90,10,0,3]'; 
initialCartesian_3{3}=[-10,110,10,0,3]'; 

initialCartesian_4{1}=[0,150,10,0,4]'; 
initialCartesian_4{2}=[-10,140,10,0,4]'; 
initialCartesian_4{3}=[-10,160,10,0,4]'; 

initialCartesian_5{1}=[0,200,10,0,5]'; 
initialCartesian_5{2}=[-10,190,10,0,5]'; 
initialCartesian_5{3}=[-10,210,10,0,5]'; 

initialCartesian_6{1}=[0,250,10,0,6]'; 
initialCartesian_6{2}=[-10,240,10,0,6]'; 
initialCartesian_6{3}=[-10,260,10,0,6]'; 

initialCartesian_7{1}=[0,300,10,0,7]'; 
initialCartesian_7{2}=[-10,290,10,0,7]'; 
initialCartesian_7{3}=[-10,310,10,0,7]'; 

initialCartesian_8{1}=[0,350,10,0,8]'; 
initialCartesian_8{2}=[-10,340,10,0,8]'; 
initialCartesian_8{3}=[-10,360,10,0,8]'; 

initialCartesian_9{1}=[0,400,10,0,9]'; 
initialCartesian_9{2}=[-10,390,10,0,9]'; 
initialCartesian_9{3}=[-10,410,10,0,9]'; 

initialCartesian_10{1}=[0,450,10,0,10]'; 
initialCartesian_10{2}=[-10,440,10,0,10]'; 
initialCartesian_10{3}=[-10,460,10,0,10]'; 

initialCartesian_11{1}=[0,500,10,0,11]'; 
initialCartesian_11{2}=[-10,490,10,0,11]'; 
initialCartesian_11{3}=[-10,510,10,0,11]'; 

initialCartesian_12{1}=[0,550,10,0,12]'; 
initialCartesian_12{2}=[-10,540,10,0,12]'; 
initialCartesian_12{3}=[-10,560,10,0,12]'; 

initialCartesian_13{1}=[0,600,10,0,13]'; 
initialCartesian_13{2}=[-10,590,10,0,13]'; 
initialCartesian_13{3}=[-10,610,10,0,13]'; 

initialCartesian_14{1}=[0,650,10,0,14]'; 
initialCartesian_14{2}=[-10,640,10,0,14]'; 
initialCartesian_14{3}=[-10,660,10,0,14]'; 

initialCartesian_15{1}=[0,700,10,0,15]'; 
initialCartesian_15{2}=[-10,690,10,0,15]'; 
initialCartesian_15{3}=[-10,710,10,0,15]'; 

initialCartesian_16{1}=[0,750,10,0,16]'; 
initialCartesian_16{2}=[-10,740,10,0,16]'; 
initialCartesian_16{3}=[-10,760,10,0,16]'; 

coordinateCartesian_1{1}=zeros(5,41);
coordinateCartesian_1{1}(5,:)=1;
coordinateCartesian_1{2}=zeros(5,41);
coordinateCartesian_1{2}(5,:)=1;
coordinateCartesian_1{3}=zeros(5,41);
coordinateCartesian_1{3}(5,:)=1;

coordinateCartesian_2{1}=zeros(5,41);
coordinateCartesian_2{1}(5,:)=2;
coordinateCartesian_2{2}=zeros(5,41);
coordinateCartesian_2{2}(5,:)=2;
coordinateCartesian_2{3}=zeros(5,41);
coordinateCartesian_2{3}(5,:)=2;

coordinateCartesian_3{1}=zeros(5,41);
coordinateCartesian_3{1}(5,:)=3;
coordinateCartesian_3{2}=zeros(5,41);
coordinateCartesian_3{2}(5,:)=3;
coordinateCartesian_3{3}=zeros(5,41);
coordinateCartesian_3{3}(5,:)=3;

coordinateCartesian_4{1}=zeros(5,41);
coordinateCartesian_4{1}(5,:)=4;
coordinateCartesian_4{2}=zeros(5,41);
coordinateCartesian_4{2}(5,:)=4;
coordinateCartesian_4{3}=zeros(5,41);
coordinateCartesian_4{3}(5,:)=4;

coordinateCartesian_5{1}=zeros(5,41);
coordinateCartesian_5{1}(5,:)=5;
coordinateCartesian_5{2}=zeros(5,41);
coordinateCartesian_5{2}(5,:)=5;
coordinateCartesian_5{3}=zeros(5,41);
coordinateCartesian_5{3}(5,:)=5;

coordinateCartesian_6{1}=zeros(5,41);
coordinateCartesian_6{1}(5,:)=6;
coordinateCartesian_6{2}=zeros(5,41);
coordinateCartesian_6{2}(5,:)=6;
coordinateCartesian_6{3}=zeros(5,41);
coordinateCartesian_6{3}(5,:)=6;

coordinateCartesian_7{1}=zeros(5,41);
coordinateCartesian_7{1}(5,:)=7;
coordinateCartesian_7{2}=zeros(5,41);
coordinateCartesian_7{2}(5,:)=7;
coordinateCartesian_7{3}=zeros(5,41);
coordinateCartesian_7{3}(5,:)=7;

coordinateCartesian_8{1}=zeros(5,41);
coordinateCartesian_8{1}(5,:)=8;
coordinateCartesian_8{2}=zeros(5,41);
coordinateCartesian_8{2}(5,:)=8;
coordinateCartesian_8{3}=zeros(5,41);
coordinateCartesian_8{3}(5,:)=8;

coordinateCartesian_9{1}=zeros(5,41);
coordinateCartesian_9{1}(5,:)=9;
coordinateCartesian_9{2}=zeros(5,41);
coordinateCartesian_9{2}(5,:)=9;
coordinateCartesian_9{3}=zeros(5,41);
coordinateCartesian_9{3}(5,:)=9;

coordinateCartesian_10{1}=zeros(5,41);
coordinateCartesian_10{1}(5,:)=10;
coordinateCartesian_10{2}=zeros(5,41);
coordinateCartesian_10{2}(5,:)=10;
coordinateCartesian_10{3}=zeros(5,41);
coordinateCartesian_10{3}(5,:)=10;

coordinateCartesian_11{1}=zeros(5,41);
coordinateCartesian_11{1}(5,:)=11;
coordinateCartesian_11{2}=zeros(5,41);
coordinateCartesian_11{2}(5,:)=11;
coordinateCartesian_11{3}=zeros(5,41);
coordinateCartesian_11{3}(5,:)=11;

coordinateCartesian_12{1}=zeros(5,41);
coordinateCartesian_12{1}(5,:)=12;
coordinateCartesian_12{2}=zeros(5,41);
coordinateCartesian_12{2}(5,:)=12;
coordinateCartesian_12{3}=zeros(5,41);
coordinateCartesian_12{3}(5,:)=12;

coordinateCartesian_13{1}=zeros(5,41);
coordinateCartesian_13{1}(5,:)=13;
coordinateCartesian_13{2}=zeros(5,41);
coordinateCartesian_13{2}(5,:)=13;
coordinateCartesian_13{3}=zeros(5,41);
coordinateCartesian_13{3}(5,:)=13;

coordinateCartesian_14{1}=zeros(5,41);
coordinateCartesian_14{1}(5,:)=14;
coordinateCartesian_14{2}=zeros(5,41);
coordinateCartesian_14{2}(5,:)=14;
coordinateCartesian_14{3}=zeros(5,41);
coordinateCartesian_14{3}(5,:)=14;

coordinateCartesian_15{1}=zeros(5,41);
coordinateCartesian_15{1}(5,:)=15;
coordinateCartesian_15{2}=zeros(5,41);
coordinateCartesian_15{2}(5,:)=15;
coordinateCartesian_15{3}=zeros(5,41);
coordinateCartesian_15{3}(5,:)=15;

coordinateCartesian_16{1}=zeros(5,41);
coordinateCartesian_16{1}(5,:)=16;
coordinateCartesian_16{2}=zeros(5,41);
coordinateCartesian_16{2}(5,:)=16;
coordinateCartesian_16{3}=zeros(5,41);
coordinateCartesian_16{3}(5,:)=16;

coordinateCartesian_1{1}(:,1)=initialCartesian_1{1};
coordinateCartesian_1{2}(:,1)=initialCartesian_1{2};
coordinateCartesian_1{3}(:,1)=initialCartesian_1{3};

coordinateCartesian_2{1}(:,1)=initialCartesian_2{1};
coordinateCartesian_2{2}(:,1)=initialCartesian_2{2};
coordinateCartesian_2{3}(:,1)=initialCartesian_2{3};

coordinateCartesian_3{1}(:,1)=initialCartesian_3{1};
coordinateCartesian_3{2}(:,1)=initialCartesian_3{2};
coordinateCartesian_3{3}(:,1)=initialCartesian_3{3};

coordinateCartesian_4{1}(:,1)=initialCartesian_4{1};
coordinateCartesian_4{2}(:,1)=initialCartesian_4{2};
coordinateCartesian_4{3}(:,1)=initialCartesian_4{3};

coordinateCartesian_5{1}(:,1)=initialCartesian_5{1};
coordinateCartesian_5{2}(:,1)=initialCartesian_5{2};
coordinateCartesian_5{3}(:,1)=initialCartesian_5{3};

coordinateCartesian_6{1}(:,1)=initialCartesian_6{1};
coordinateCartesian_6{2}(:,1)=initialCartesian_6{2};
coordinateCartesian_6{3}(:,1)=initialCartesian_6{3};

coordinateCartesian_7{1}(:,1)=initialCartesian_7{1};
coordinateCartesian_7{2}(:,1)=initialCartesian_7{2};
coordinateCartesian_7{3}(:,1)=initialCartesian_7{3};

coordinateCartesian_8{1}(:,1)=initialCartesian_8{1};
coordinateCartesian_8{2}(:,1)=initialCartesian_8{2};
coordinateCartesian_8{3}(:,1)=initialCartesian_8{3};

coordinateCartesian_9{1}(:,1)=initialCartesian_9{1};
coordinateCartesian_9{2}(:,1)=initialCartesian_9{2};
coordinateCartesian_9{3}(:,1)=initialCartesian_9{3};

coordinateCartesian_10{1}(:,1)=initialCartesian_10{1};
coordinateCartesian_10{2}(:,1)=initialCartesian_10{2};
coordinateCartesian_10{3}(:,1)=initialCartesian_10{3};

coordinateCartesian_11{1}(:,1)=initialCartesian_11{1};
coordinateCartesian_11{2}(:,1)=initialCartesian_11{2};
coordinateCartesian_11{3}(:,1)=initialCartesian_11{3};

coordinateCartesian_12{1}(:,1)=initialCartesian_12{1};
coordinateCartesian_12{2}(:,1)=initialCartesian_12{2};
coordinateCartesian_12{3}(:,1)=initialCartesian_12{3};

coordinateCartesian_13{1}(:,1)=initialCartesian_13{1};
coordinateCartesian_13{2}(:,1)=initialCartesian_13{2};
coordinateCartesian_13{3}(:,1)=initialCartesian_13{3};

coordinateCartesian_14{1}(:,1)=initialCartesian_14{1};
coordinateCartesian_14{2}(:,1)=initialCartesian_14{2};
coordinateCartesian_14{3}(:,1)=initialCartesian_14{3};

coordinateCartesian_15{1}(:,1)=initialCartesian_15{1};
coordinateCartesian_15{2}(:,1)=initialCartesian_15{2};
coordinateCartesian_15{3}(:,1)=initialCartesian_15{3};

coordinateCartesian_16{1}(:,1)=initialCartesian_16{1};
coordinateCartesian_16{2}(:,1)=initialCartesian_16{2};
coordinateCartesian_16{3}(:,1)=initialCartesian_16{3};

sampleInterval=0.5; %采样间隔0.5s
idxTime=zeros(1,41);  %时间序号
for idxSample=2:41 %采样间隔是0.5s，所以20s要采样40次
    idxTime(idxSample)=idxTime(idxSample-1)+sampleInterval;
end

coordinateCartesian_1{1}=move(coordinateCartesian_1{1},sampleInterval);
coordinateCartesian_1{2}=move(coordinateCartesian_1{2},sampleInterval);
coordinateCartesian_1{3}=move(coordinateCartesian_1{3},sampleInterval);
coordinateCartesian_2{1}=move(coordinateCartesian_2{1},sampleInterval);
coordinateCartesian_2{2}=move(coordinateCartesian_2{2},sampleInterval);
coordinateCartesian_2{3}=move(coordinateCartesian_2{3},sampleInterval);
coordinateCartesian_3{1}=move(coordinateCartesian_3{1},sampleInterval);
coordinateCartesian_3{2}=move(coordinateCartesian_3{2},sampleInterval);
coordinateCartesian_3{3}=move(coordinateCartesian_3{3},sampleInterval);
coordinateCartesian_4{1}=move(coordinateCartesian_4{1},sampleInterval);
coordinateCartesian_4{2}=move(coordinateCartesian_4{2},sampleInterval);
coordinateCartesian_4{3}=move(coordinateCartesian_4{3},sampleInterval);
coordinateCartesian_5{1}=move(coordinateCartesian_5{1},sampleInterval);
coordinateCartesian_5{2}=move(coordinateCartesian_5{2},sampleInterval);
coordinateCartesian_5{3}=move(coordinateCartesian_5{3},sampleInterval);
coordinateCartesian_6{1}=move(coordinateCartesian_6{1},sampleInterval);
coordinateCartesian_6{2}=move(coordinateCartesian_6{2},sampleInterval);
coordinateCartesian_6{3}=move(coordinateCartesian_6{3},sampleInterval);
coordinateCartesian_7{1}=move(coordinateCartesian_7{1},sampleInterval);
coordinateCartesian_7{2}=move(coordinateCartesian_7{2},sampleInterval);
coordinateCartesian_7{3}=move(coordinateCartesian_7{3},sampleInterval);
coordinateCartesian_8{1}=move(coordinateCartesian_8{1},sampleInterval);
coordinateCartesian_8{2}=move(coordinateCartesian_8{2},sampleInterval);
coordinateCartesian_8{3}=move(coordinateCartesian_8{3},sampleInterval);
coordinateCartesian_9{1}=move(coordinateCartesian_9{1},sampleInterval);
coordinateCartesian_9{2}=move(coordinateCartesian_9{2},sampleInterval);
coordinateCartesian_9{3}=move(coordinateCartesian_9{3},sampleInterval);
coordinateCartesian_10{1}=move(coordinateCartesian_10{1},sampleInterval);
coordinateCartesian_10{2}=move(coordinateCartesian_10{2},sampleInterval);
coordinateCartesian_10{3}=move(coordinateCartesian_10{3},sampleInterval);
coordinateCartesian_11{1}=move(coordinateCartesian_11{1},sampleInterval);
coordinateCartesian_11{2}=move(coordinateCartesian_11{2},sampleInterval);
coordinateCartesian_11{3}=move(coordinateCartesian_11{3},sampleInterval);
coordinateCartesian_12{1}=move(coordinateCartesian_12{1},sampleInterval);
coordinateCartesian_12{2}=move(coordinateCartesian_12{2},sampleInterval);
coordinateCartesian_12{3}=move(coordinateCartesian_12{3},sampleInterval);
coordinateCartesian_13{1}=move(coordinateCartesian_13{1},sampleInterval);
coordinateCartesian_13{2}=move(coordinateCartesian_13{2},sampleInterval);
coordinateCartesian_13{3}=move(coordinateCartesian_13{3},sampleInterval);
coordinateCartesian_14{1}=move(coordinateCartesian_14{1},sampleInterval);
coordinateCartesian_14{2}=move(coordinateCartesian_14{2},sampleInterval);
coordinateCartesian_14{3}=move(coordinateCartesian_14{3},sampleInterval);
coordinateCartesian_15{1}=move(coordinateCartesian_15{1},sampleInterval);
coordinateCartesian_15{2}=move(coordinateCartesian_15{2},sampleInterval);
coordinateCartesian_15{3}=move(coordinateCartesian_15{3},sampleInterval);
coordinateCartesian_16{1}=move(coordinateCartesian_16{1},sampleInterval);
coordinateCartesian_16{2}=move(coordinateCartesian_16{2},sampleInterval);
coordinateCartesian_16{3}=move(coordinateCartesian_16{3},sampleInterval);

plot(coordinateCartesian_1{1}(1,1:5:41),coordinateCartesian_1{1}(2,1:5:41),'ro');
grid on;
hold on;
%axis equal;
% axis([0 500 -200 100]);
% plot(coordinateCartesian_1{1}(1,:),coordinateCartesian_1{1}(3,:),'r');
plot(coordinateCartesian_1{2}(1,1:5:41),coordinateCartesian_1{2}(2,1:5:41),'r+');
plot(coordinateCartesian_1{3}(1,1:5:41),coordinateCartesian_1{3}(2,1:5:41),'r*');
plot(coordinateCartesian_2{1}(1,1:5:41),coordinateCartesian_2{1}(2,1:5:41),'bo');
plot(coordinateCartesian_2{2}(1,1:5:41),coordinateCartesian_2{2}(2,1:5:41),'b+');
plot(coordinateCartesian_2{3}(1,1:5:41),coordinateCartesian_2{3}(2,1:5:41),'b*');
plot(coordinateCartesian_3{1}(1,1:5:41),coordinateCartesian_3{1}(2,1:5:41),'ro');
plot(coordinateCartesian_3{2}(1,1:5:41),coordinateCartesian_3{2}(2,1:5:41),'r+');
plot(coordinateCartesian_3{3}(1,1:5:41),coordinateCartesian_3{3}(2,1:5:41),'r*');
plot(coordinateCartesian_4{1}(1,1:5:41),coordinateCartesian_4{1}(2,1:5:41),'bo');
plot(coordinateCartesian_4{2}(1,1:5:41),coordinateCartesian_4{2}(2,1:5:41),'b+');
plot(coordinateCartesian_4{3}(1,1:5:41),coordinateCartesian_4{3}(2,1:5:41),'b*');
plot(coordinateCartesian_5{1}(1,1:5:41),coordinateCartesian_5{1}(2,1:5:41),'ro');
plot(coordinateCartesian_5{2}(1,1:5:41),coordinateCartesian_5{2}(2,1:5:41),'r+');
plot(coordinateCartesian_5{3}(1,1:5:41),coordinateCartesian_5{3}(2,1:5:41),'r*');
plot(coordinateCartesian_6{1}(1,1:5:41),coordinateCartesian_6{1}(2,1:5:41),'bo');
plot(coordinateCartesian_6{2}(1,1:5:41),coordinateCartesian_6{2}(2,1:5:41),'b+');
plot(coordinateCartesian_6{3}(1,1:5:41),coordinateCartesian_6{3}(2,1:5:41),'b*');
plot(coordinateCartesian_7{1}(1,1:5:41),coordinateCartesian_7{1}(2,1:5:41),'ro');
plot(coordinateCartesian_7{2}(1,1:5:41),coordinateCartesian_7{2}(2,1:5:41),'r+');
plot(coordinateCartesian_7{3}(1,1:5:41),coordinateCartesian_7{3}(2,1:5:41),'r*');
plot(coordinateCartesian_8{1}(1,1:5:41),coordinateCartesian_8{1}(2,1:5:41),'bo');
plot(coordinateCartesian_8{2}(1,1:5:41),coordinateCartesian_8{2}(2,1:5:41),'b+');
plot(coordinateCartesian_8{3}(1,1:5:41),coordinateCartesian_8{3}(2,1:5:41),'b*');
plot(coordinateCartesian_9{1}(1,1:5:41),coordinateCartesian_9{1}(2,1:5:41),'ro');
plot(coordinateCartesian_9{2}(1,1:5:41),coordinateCartesian_9{2}(2,1:5:41),'r+');
plot(coordinateCartesian_9{3}(1,1:5:41),coordinateCartesian_9{3}(2,1:5:41),'r*');
plot(coordinateCartesian_10{1}(1,1:5:41),coordinateCartesian_10{1}(2,1:5:41),'bo');
plot(coordinateCartesian_10{2}(1,1:5:41),coordinateCartesian_10{2}(2,1:5:41),'b+');
plot(coordinateCartesian_10{3}(1,1:5:41),coordinateCartesian_10{3}(2,1:5:41),'b*');
plot(coordinateCartesian_11{1}(1,1:5:41),coordinateCartesian_11{1}(2,1:5:41),'ro');
plot(coordinateCartesian_11{2}(1,1:5:41),coordinateCartesian_11{2}(2,1:5:41),'r+');
plot(coordinateCartesian_11{3}(1,1:5:41),coordinateCartesian_11{3}(2,1:5:41),'r*');
plot(coordinateCartesian_12{1}(1,1:5:41),coordinateCartesian_12{1}(2,1:5:41),'bo');
plot(coordinateCartesian_12{2}(1,1:5:41),coordinateCartesian_12{2}(2,1:5:41),'b+');
plot(coordinateCartesian_12{3}(1,1:5:41),coordinateCartesian_12{3}(2,1:5:41),'b*');
plot(coordinateCartesian_13{1}(1,1:5:41),coordinateCartesian_13{1}(2,1:5:41),'ro');
plot(coordinateCartesian_13{2}(1,1:5:41),coordinateCartesian_13{2}(2,1:5:41),'r+');
plot(coordinateCartesian_13{3}(1,1:5:41),coordinateCartesian_13{3}(2,1:5:41),'r*');
plot(coordinateCartesian_14{1}(1,1:5:41),coordinateCartesian_14{1}(2,1:5:41),'bo');
plot(coordinateCartesian_14{2}(1,1:5:41),coordinateCartesian_14{2}(2,1:5:41),'b+');
plot(coordinateCartesian_14{3}(1,1:5:41),coordinateCartesian_14{3}(2,1:5:41),'b*');
plot(coordinateCartesian_15{1}(1,1:5:41),coordinateCartesian_15{1}(2,1:5:41),'ro');
plot(coordinateCartesian_15{2}(1,1:5:41),coordinateCartesian_15{2}(2,1:5:41),'r+');
plot(coordinateCartesian_15{3}(1,1:5:41),coordinateCartesian_15{3}(2,1:5:41),'r*');
plot(coordinateCartesian_16{1}(1,1:5:41),coordinateCartesian_16{1}(2,1:5:41),'bo');
plot(coordinateCartesian_16{2}(1,1:5:41),coordinateCartesian_16{2}(2,1:5:41),'b+');
plot(coordinateCartesian_16{3}(1,1:5:41),coordinateCartesian_16{3}(2,1:5:41),'b*');

coordinateCartesian_1{1}=[idxTime;coordinateCartesian_1{1}];
coordinateCartesian_1{2}=[idxTime;coordinateCartesian_1{2}];
coordinateCartesian_1{3}=[idxTime;coordinateCartesian_1{3}];
coordinateCartesian_2{1}=[idxTime;coordinateCartesian_2{1}];
coordinateCartesian_2{2}=[idxTime;coordinateCartesian_2{2}];
coordinateCartesian_2{3}=[idxTime;coordinateCartesian_2{3}];
coordinateCartesian_3{1}=[idxTime;coordinateCartesian_3{1}];
coordinateCartesian_3{2}=[idxTime;coordinateCartesian_3{2}];
coordinateCartesian_3{3}=[idxTime;coordinateCartesian_3{3}];
coordinateCartesian_4{1}=[idxTime;coordinateCartesian_4{1}];
coordinateCartesian_4{2}=[idxTime;coordinateCartesian_4{2}];
coordinateCartesian_4{3}=[idxTime;coordinateCartesian_4{3}];
coordinateCartesian_5{1}=[idxTime;coordinateCartesian_5{1}];
coordinateCartesian_5{2}=[idxTime;coordinateCartesian_5{2}];
coordinateCartesian_5{3}=[idxTime;coordinateCartesian_5{3}];
coordinateCartesian_6{1}=[idxTime;coordinateCartesian_6{1}];
coordinateCartesian_6{2}=[idxTime;coordinateCartesian_6{2}];
coordinateCartesian_6{3}=[idxTime;coordinateCartesian_6{3}];
coordinateCartesian_7{1}=[idxTime;coordinateCartesian_7{1}];
coordinateCartesian_7{2}=[idxTime;coordinateCartesian_7{2}];
coordinateCartesian_7{3}=[idxTime;coordinateCartesian_7{3}];
coordinateCartesian_8{1}=[idxTime;coordinateCartesian_8{1}];
coordinateCartesian_8{2}=[idxTime;coordinateCartesian_8{2}];
coordinateCartesian_8{3}=[idxTime;coordinateCartesian_8{3}];
coordinateCartesian_9{1}=[idxTime;coordinateCartesian_9{1}];
coordinateCartesian_9{2}=[idxTime;coordinateCartesian_9{2}];
coordinateCartesian_9{3}=[idxTime;coordinateCartesian_9{3}];
coordinateCartesian_10{1}=[idxTime;coordinateCartesian_10{1}];
coordinateCartesian_10{2}=[idxTime;coordinateCartesian_10{2}];
coordinateCartesian_10{3}=[idxTime;coordinateCartesian_10{3}];
coordinateCartesian_11{1}=[idxTime;coordinateCartesian_11{1}];
coordinateCartesian_11{2}=[idxTime;coordinateCartesian_11{2}];
coordinateCartesian_11{3}=[idxTime;coordinateCartesian_11{3}];
coordinateCartesian_12{1}=[idxTime;coordinateCartesian_12{1}];
coordinateCartesian_12{2}=[idxTime;coordinateCartesian_12{2}];
coordinateCartesian_12{3}=[idxTime;coordinateCartesian_12{3}];
coordinateCartesian_13{1}=[idxTime;coordinateCartesian_13{1}];
coordinateCartesian_13{2}=[idxTime;coordinateCartesian_13{2}];
coordinateCartesian_13{3}=[idxTime;coordinateCartesian_13{3}];
coordinateCartesian_14{1}=[idxTime;coordinateCartesian_14{1}];
coordinateCartesian_14{2}=[idxTime;coordinateCartesian_14{2}];
coordinateCartesian_14{3}=[idxTime;coordinateCartesian_14{3}];
coordinateCartesian_15{1}=[idxTime;coordinateCartesian_15{1}];
coordinateCartesian_15{2}=[idxTime;coordinateCartesian_15{2}];
coordinateCartesian_15{3}=[idxTime;coordinateCartesian_15{3}];
coordinateCartesian_16{1}=[idxTime;coordinateCartesian_16{1}];
coordinateCartesian_16{2}=[idxTime;coordinateCartesian_16{2}];
coordinateCartesian_16{3}=[idxTime;coordinateCartesian_16{3}];

coordinateCartesian_all=zeros(6,1968); %41*48=1968
coordinateCartesian_all(:, 1:48:1921)=coordinateCartesian_1{1};
coordinateCartesian_all(:, 2:48:1922)=coordinateCartesian_1{2};
coordinateCartesian_all(:, 3:48:1923)=coordinateCartesian_1{3};
coordinateCartesian_all(:, 4:48:1924)=coordinateCartesian_2{1};
coordinateCartesian_all(:, 5:48:1925)=coordinateCartesian_2{2};
coordinateCartesian_all(:, 6:48:1926)=coordinateCartesian_2{3};
coordinateCartesian_all(:, 7:48:1927)=coordinateCartesian_3{1};
coordinateCartesian_all(:, 8:48:1928)=coordinateCartesian_3{2};
coordinateCartesian_all(:, 9:48:1929)=coordinateCartesian_3{3};
coordinateCartesian_all(:, 10:48:1930)=coordinateCartesian_4{1};
coordinateCartesian_all(:, 11:48:1931)=coordinateCartesian_4{2};
coordinateCartesian_all(:, 12:48:1932)=coordinateCartesian_4{3};
coordinateCartesian_all(:, 13:48:1933)=coordinateCartesian_5{1};
coordinateCartesian_all(:, 14:48:1934)=coordinateCartesian_5{2};
coordinateCartesian_all(:, 15:48:1935)=coordinateCartesian_5{3};
coordinateCartesian_all(:, 16:48:1936)=coordinateCartesian_6{1};
coordinateCartesian_all(:, 17:48:1937)=coordinateCartesian_6{2};
coordinateCartesian_all(:, 18:48:1938)=coordinateCartesian_6{3};
coordinateCartesian_all(:, 19:48:1939)=coordinateCartesian_7{1};
coordinateCartesian_all(:, 20:48:1940)=coordinateCartesian_7{2};
coordinateCartesian_all(:, 21:48:1941)=coordinateCartesian_7{3};
coordinateCartesian_all(:, 22:48:1942)=coordinateCartesian_8{1};
coordinateCartesian_all(:, 23:48:1943)=coordinateCartesian_8{2};
coordinateCartesian_all(:, 24:48:1944)=coordinateCartesian_8{3};
coordinateCartesian_all(:, 25:48:1945)=coordinateCartesian_9{1};
coordinateCartesian_all(:, 26:48:1946)=coordinateCartesian_9{2};
coordinateCartesian_all(:, 27:48:1947)=coordinateCartesian_9{3};
coordinateCartesian_all(:, 28:48:1948)=coordinateCartesian_10{1};
coordinateCartesian_all(:, 29:48:1949)=coordinateCartesian_10{2};
coordinateCartesian_all(:, 30:48:1950)=coordinateCartesian_10{3};
coordinateCartesian_all(:, 31:48:1951)=coordinateCartesian_11{1};
coordinateCartesian_all(:, 32:48:1952)=coordinateCartesian_11{2};
coordinateCartesian_all(:, 33:48:1953)=coordinateCartesian_11{3};
coordinateCartesian_all(:, 34:48:1954)=coordinateCartesian_12{1};
coordinateCartesian_all(:, 35:48:1955)=coordinateCartesian_12{2};
coordinateCartesian_all(:, 36:48:1956)=coordinateCartesian_12{3};
coordinateCartesian_all(:, 37:48:1957)=coordinateCartesian_13{1};
coordinateCartesian_all(:, 38:48:1958)=coordinateCartesian_13{2};
coordinateCartesian_all(:, 39:48:1959)=coordinateCartesian_13{3};
coordinateCartesian_all(:, 40:48:1960)=coordinateCartesian_14{1};
coordinateCartesian_all(:, 41:48:1961)=coordinateCartesian_14{2};
coordinateCartesian_all(:, 42:48:1962)=coordinateCartesian_14{3};
coordinateCartesian_all(:, 43:48:1963)=coordinateCartesian_15{1};
coordinateCartesian_all(:, 44:48:1964)=coordinateCartesian_15{2};
coordinateCartesian_all(:, 45:48:1965)=coordinateCartesian_15{3};
coordinateCartesian_all(:, 46:48:1966)=coordinateCartesian_16{1};
coordinateCartesian_all(:, 47:48:1967)=coordinateCartesian_16{2};
coordinateCartesian_all(:, 48:48:1968)=coordinateCartesian_16{3};

% % plot(coordinateCartesian_all(1,:),coordinateCartesian_all(3,:),'o');
dlmwrite('data.txt', coordinateCartesian_all', 'delimiter', '\t', 'newline', 'pc','precision',  '%.2f');