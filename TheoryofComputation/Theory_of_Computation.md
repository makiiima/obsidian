# Theory of Computation

An alphabet is a *finite* set of symbols.

> can be an empty set

A string is a *finite* sequence of symbols from some alphabet.

>$\Sigma=\{0,1\}$  ,so 0,1,01,10,010,... are strings over $\Sigma$

The length of $|w |$= number of symbols in $w$.

The empty string $e$ with $|e|=0$

$ \Sigma^i$ = the set of all strings of length i over $\Sigma$

$\Sigma^+ = \bigcup_{i\geq 1}\Sigma^i$

$\Sigma^* = \bigcup_{i\geq 0}\Sigma^i=\Sigma^+ \cup\{e\}$



String Operations

- concatenation
  $u=a_1a_2...a_i, v=b_1...b_j,\ w=uv=a_1...a_ib_1...b_j$
  $u=123,\ v=456,\ uv=123456$

- exponentiation
  $w^i=w...w(i \ times)$
  $w=01,\ w^0=e,\ w^1=01,\ w^2=0101...$

- reversal
  $w=a_1...a_i,\ w^R=a_i...a_1$

  $w=123,\ w^R=321$

Any $L \subseteq \Sigma^*$ is called a language over $\Sigma$
>$$
>\Sigma={0,1}\\
>L_1=\empty\\
>L_2=\Sigma^*\\
>L_3=\{0^n1^n,n\geq0\}\\
>L_4=\{e\}
>$$

Decision->Language

Given a string x, is x $\subseteq$ L?



finite automata

initial state is unique

final state can be several

A finite automata

- $\Sigma$: input alphabet
- $K$: a *finite* set of states
- $s\in K$: initial state
- $F\subseteq K$: the set of final states
- $\delta:\ K_{\text{current\ state}}\times \Sigma \rightarrow K_{\text{next\ state}} $

A configuration is an element of $K_{\text{current}}\times \Sigma^*(\text{unread input})$

$(q_1,1010)\vdash_M(q_2,010)\vdash_M(q_3,10)\vdash_M(q_2,0)\vdash_M(q_3,e)$

$\vdash_M$: yields in one step

$(q,w)\vdash_M(q',w)$ if $w=aw'$ for some $a\in\Sigma$ and $\delta(q,a)=q'$

$(q,w)\vdash_M^*(q',w)$ if $(q',w')=(q,w)$ or $(q,w)\vdash_M...\vdash_M(q',w')$

$M\ \text{accept} \ w\in\Sigma^*\  \text{if}\ (s,w)\vdash^*_M(q,e)\ \text{for some}\ q\in F$

$L(M)=\{w\in\Sigma^*,\ \text{M accepts w}\}$

M accepts L(M), and L(M) is unique

**A language is regular if it is accepted by some FA.**



Regular Operations

- Union: $A\cup B=\{w,w\in A\ \text{or}\ w \in B\}$
- Concatenation: $A \circ B=\{ab, a\in A\  \text{and }b\in B\}$
- Star: $A^*=\{w_1w_2...w_k,w_i\in A\text{ and }K \geq 0\}$

Theorem

​	If A and B are regular, so is $A\cup B$. (The class of regular languages is closed under **union**)

Idea
$$
\exist M_1 \text{ accepting }A, M_2 \text{ accepting }B\rightarrow \exist M_3\text{ accepting }A\cup B
$$
