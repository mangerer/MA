% kv = 50000;
% dv = 20000;
% kappav = 50000;
% deltav = 20000;
% mv = 10;
% jv = 1;
% 
% m0 = 10;
% j0 = 1;
% g = [0;0;0];
% 
% m1 = 10; 
% m2 = 10;
% m3 = 10; 
% m4 = 10;
% miv = 10;
% j1 = 10;
% j2 = 10;
% j3 = 10;
% j4 = 10;
% jiv = 1;
% 
% ks = 500; %500
% ds = 10000; %300
% kappas = 500;   %500
% deltas = 10000; %300
% 
% r = [1 0 0 0 1 0 -1 0 0 0 -1 0]';
% rv = [1 0 0 0 1 0 -1 0 0 0 -1 0]';

%%Values according to Caccvale Villani paper
kv = 700;
dv = 1500;
kappav = 700;
deltav = 1500;


m0 = 1.4;
j0 = 0.2;
g = [0;0;0];

m1 = 10; 
m2 = 10;
m3 = 10; 
m4 = 10;
miv = 10;
j1 = 0.5;
j2 = 0.5;
j3 = 0.5;
j4 = 0.5;
jiv = 0.5;
mv = m0*1;
jv = j0*1;

ks = 180; %500
ds = 900; %300
kappas = ks/20;   %500
deltas = ds/20; %300

r = 0.4*[1 0 0 0 1 0 -1 0 0 0 -1 0]';
rv = 0.4*[1 0 0 0 1 0 -1 0 0 0 -1 0]';