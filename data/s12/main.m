%function main()
% MAIN ������
% �����붨12�Ĳ�������
%����5�У�[t, x, y, v, seta]
% �ֱ����ʱ�䡢x��λ�ã�y��λ�ã��ٶȴ�С���ٶȷ���

tic;
clc;
samplePoint=86401;
initial1=[0,0,20,0];
sampleInterval=1; %�������1s
coordinate1=zeros(4,samplePoint); %�洢Ŀ��1��������ʱ�̵�״ֵ̬���д洢
idxTime1=zeros(1,samplePoint); %Ŀ��1ʱ�����
coordinate1(:,1)=initial1;
%%Ŀ��1���˶�
%���������1s������24hҪ����86400��
for idxSample=2:samplePoint  %�ȼ����˶�
    idxTime1(idxSample)=idxTime1(idxSample-1)+sampleInterval;
    coordinate1(1,idxSample) = coordinate1(1,idxSample-1) + ...
                coordinate1(3,idxSample-1)*cos(coordinate1(4,idxSample-1))*sampleInterval;
    coordinate1(2,idxSample) = coordinate1(2,idxSample-1);    
    coordinate1(3,idxSample) = coordinate1(3,idxSample-1);
    coordinate1(4,idxSample) = coordinate1(4,idxSample-1);
end

coordinate1(2:5,:)=coordinate1;
%������Ŀ������ݺ���һ��
coordinate1(1,:)=idxTime1;
dlmwrite('data.txt', coordinate1', 'delimiter', '\t', 'newline', 'pc','precision',  '%.2f');
toc;