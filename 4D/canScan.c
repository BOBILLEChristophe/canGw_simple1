  // ----------------------------------------------------
  // Nom utilisateur (OS) : Christophe
  // Date et heure : 29/10/19, 23:28:29
  // -------------------------------------------------------------------------------------
  // Méthode : canScan
  // Description
  // 
  //
  // Paramètres :
  // $1 : IP distante
  // $2 : Port
  // $3 : Message à envoyer
  // $4 : Message attendu en retour
  // $5 : Connexion synchrone = 0, asynchrone = 1
  // * En mode asynchrone, les commandes Internet de 4D rendent la main au moteur de 4D
  //    immédiatement après leur exécution, sans attendre la fin du process de connexion 
  //   (c’est-à-dire, sans attendre que la connexion avec le serveur distant soit établie).
  //   Le mode asynchrone est utile lorsque vous souhaitez que les commandes TCP ne consomment pas le temps machine de 4D.
  // * En mode synchrone, les commandes Internet de 4D ne rendent la main au moteur de 4D
  //   (c’est-à-dire aux autres process de 4D) que lorsque le process de connexion a pris fin(que la connexion ait réussi ou non).
  //
  // $0 : retourne l'état 0 = connexion ok; -1 = problème
  // -------------------------------------------------------------------------------------


C_TEXTE($1;$3;$4)
C_ENTIER($0;$2;$5)

C_TEXTE($str_ip;$str_send;str_callBackMsg)
C_ENTIER($err;$int_port;$int_tcpId;$int_async)
C_ENTIER LONG($intl_tcp_id)

$str_ip:=$1
$int_port:=$2
$str_send:=$3
str_callBackMsg:=$4
$int_async:=0

Si (Nombre de parametres=5)
C_ENTIER($5)
$int_async:=$5
Fin de si 


  // Ouverture de la connexion
Boucle ($i;1;10)
$err:=TCP_Open ($str_ip;$int_port;$intl_tcp_id;$int_async)
Si ($err=0)
$i:=10
Sinon 
ENDORMIR PROCESS(Numero du process courant;1)
Fin de si 
Fin de boucle 


Au cas ou 

: ($err#0)
  // connection failed
<>errScan1:="Impossible d'ouvrir une connection TCP"

: ($err=0)
C_TEXTE(<>bufferCan1)
C_TEXTE($str_returnMsg;$str_tampon)
C_ENTIER($compt;$int_etat;)
<>quitScan1:=Faux
$compt:=0
$str_returnMsg:=""
$str_tampon:=""
$int_etat:=0
Repeter 
$erreur:=TCP_Receive ($intl_tcp_id;$str_tampon)
$erreur:=TCP_State ($intl_tcp_id;$int_etat)
Si ($str_tampon#"")
<>bufferCan1:=<>bufferCan1+$str_tampon+"\n"
Fin de si 
ENDORMIR PROCESS(Numero du process courant;1)
Jusque (($int_etat=0) | ($erreur#0) | (<>quitScan1=Vrai))


  // <>quitScan1 est une variable globale externe qui permet d'avorter la méthode à distance
  // $int_etat=0, le serveur distant a coupé la communication
  // $erreur#0, une erreur est intervenue


Au cas ou 
: (<>quitScan1=Vrai)
<>errScan1:="Process avorté par l'utilisateur"
: ($int_etat=0)
<>errScan1:="Connection coupée par le serveur"
Fin de cas 

$err:=TCP_Close ($intl_tcp_id)
Fin de cas 
