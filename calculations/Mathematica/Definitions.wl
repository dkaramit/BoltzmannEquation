(* ::Package:: *)

(* ::Section:: *)
(*Definitions*)


theta[T_?NumericQ]:=Module[{},If[T>=TC,Return[0],Return[1]]];
Gtheta[x_?NumberQ]:=Module[{},If[x>0,Return[1],Return[0]]];


(*SM parameters*)
mz=91.1876;
mt=173.;
cw=Sqrt[1-sw^2];
sw=0.474;
mw=mz*cw;
g=Sqrt[(4\[Pi])/128.9]/sw;
vev=(2mw)/g;
mh0=125.18;



(*This is how you really calculate TC and c*)
(*gU1 = g sw/cw;
yt = 173/vev*Sqrt[2];
mu = I mh0;
lam = -mu^2/vev^2 // N;
Cc = 1/16 (gU1^2 + 3 g^2 + 4 yt^2 + 8 mh0^2/vev^2);
TC = vev (1/2+(3g^2+gU1^2+4 yt^2)/(8 lam ) )^(-1/2) //Re(*from 0805.1677*);
*)

(*From hep-ph/9901312*)
Cc=( 2mw^2+mz^2+ 2mt^2+  mh0^2)/(4 vev^2);
TC=mh0/Sqrt[2Cc];

vevT[T_?NumericQ]=vev*(1-(T/TC)^2)^(0.5)//Re;


mhT[T_?NumericQ]=Module[{},
If[T>=TC,
Return[10^-10+Sqrt[Cc (T^2-TC^2)]//Re],
Return[10^-10+Sqrt[mh0^2 - 2 Cc*T^2]//Re]
]
];


(*logspace and linspace always useful...*)
logspace[a_,b_,n_]:=10^Range[a,b,(b-a)/(n-1)]//N;
linspace[a_,b_,n_]:=Range[a,b,(b-a)/(n-1)]//N;


(*=====================================================*)
If[ValueQ[NKer],
LaunchKernels[NKer],
LaunchKernels[$KernelCount]
]

Needs["NumericalCalculus`"];
(*=====================================================*)


(*Make tables for geff, heff, H, etc*)
tab=Import["data/eos2020.dat"];
Ttab=tab[[All,1]];
Tmin=Min[Ttab];
Tmax=Max[Ttab];
Ltab=Length[tab];
hint0[T_]=Interpolation[Table[ {tab[[i,1]],tab[[i,2]]},{i,1,Ltab} ]][T];
gint0[T_]=Interpolation[Table[ {tab[[i,1]],tab[[i,3]]},{i,1,Ltab} ]][T];

hint[T_?NumericQ]:=Module[{},
If[T>Tmax,
Return[ tab[[Ltab,2]] ],
Return[ hint0[T]]
  ];
];

gint[T_?NumericQ]:=Module[{},
If[T>Tmax,
Return[ tab[[Ltab,3]] ],
Return[ gint0[T]]
  ];
];

dloghdTtab=Table[{T,ND[Log[hint[t]],t,T]},{T,logspace[-10,4,10^3]}];
dloghdTint0[T_]=Interpolation[dloghdTtab][T];

dh[T_?NumericQ]:=Module[{},
If[T<=10^-10||T>10^3,Return[0]];
Return[1+1/3.*T*dloghdTint0[T]]
];
(*=========================Hubble in GeV and entropy density============================*)
Hubble[T_?NumericQ]:=Module[{\[Rho],mP},
mP=1.22 10^19.;
\[Rho]=N[ (\[Pi]^2)/30  T^4]gint[T];
Return[N[((8 \[Pi])/(3 mP^2) \[Rho])^(1/2.)]]
];
s[T_?NumericQ]:=Module[{},N[(2\[Pi]^2)/45.]hint[T]T^3];
rho[T_?NumericQ]:=Module[{},N[(\[Pi]^2)/30.]gint[T]T^4];
mP=1.22 10^19. (*Planck constant in GeV*);


