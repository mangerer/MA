
 syms Sr1 Sr2 Sr3 Sr4 mv jv m1 j1 m2 j2 dpv omega real



A4 = [-1 0 1 0 0 0 0 0 0 0;
    Sr1 -1 0 1 0 0 0 0 0 0; 
    -1 0 0 0 1 0 0 0 0 0;
    Sr2 -1 0 0 0 1 0 0 0 0;
    -1 0 0 0 0 0 1 0 0 0;
    Sr3 -1 0 0 0 0 0 1 0 0
    -1 0 0 0 0 0 0 0 1 0
    Sr4 -1 0 0 0 0 0 0 0 1];

nA4b = [1 0; 0 1; 1 0; -Sr1 1; 1 0; -Sr2 1; 1 0; -Sr3 1; 1 0; -Sr4 1];

nA4 = null(A4);

A2T = [-1 0 1 0 0 0 ;
    Sr1 -1 0 1 0 0 ; 
    -1 0 0 0 1 0 ;
    Sr2 -1 0 0 0 1 ];

nA2 = null(A2T);
nA2b = [1 0; 0 1; 1 0; -Sr1 1; 1 0; -Sr2 1];
M2 = blkdiag(mv,jv,m1,j1,m2,j2);
S2 = [mv 0; 0 jv; m1 0; -Sr1*j1 j1; m2 0; -Sr2*j2 j2];
%Mq = nA2b' * [jv*omega;mv*dpv;j1*omega;m1*dpv+m1*Sr1*omega;j2*omega;m2*dpv+m2*Sr2*omega]
M2bar = (S2'*M2^-1*S2)^-1