  // ----------------------------------------------------
  // Nom utilisateur (OS) : Christophe
  // Date et heure : 29/10/19, 21:12:10
  // -------------------------------------------------------------------------------------
  // Méthode : canScan0
  // Description
  // 
  //
  // Paramètres :
  // -------------------------------------------------------------------------------------

C_TEXTE($str_ip;$str_data;<>errScan1)
C_ENTIER($int_port)
<>errScan1:="Lancement du process"
$str_ip:="192.168.1.78"
$int_port:=12560

C_ENTIER($err;$actif)
C_ENTIER LONG($vlProcessID)
$err:=NET_Ping ($str_ip;"";$actif;0)
Si ($err=0)

C_ENTIER($int_async)
$str_data:=""
$int_async:=0  // 0 = asynch, 1 = synch
  //Lancement du process de scan
$vlProcessID:=Nouveau process("canScan";512*1024;"Scan du bus can : "+$str_ip+":"+Chaine($int_port);$str_ip;$int_port;$str_data;$int_async)

Sinon 
<>errScan1:="Pbme de cpnnexion au serveur distant"
Fin de si 

C_TEXTE($str_dataBuff)
C_ENTIER($posSeparateur)
Tant que ((<>quitScan1=Faux) & (Longueur(<>bufferCan1)>0))
$posSeparateur:=Position("\n";<>bufferCan1)
Si ($posSeparateur>0)
  // traitement des données.
  // Ici on se contente de vider le buffer sans s'occuper de l'utilisation des données.
$str_dataBuff:=Sous chaine(<>bufferCan1;0;Position("\n";<>bufferCan1)-1)
<>bufferCan1:=Supprimer chaine(<>bufferCan1;0;$posSeparateur)
Fin de si 
Fin tant que 

TRACE
<>quitScan1:=Vrai  // Avorter le process
$test:=<>errScan1  // Statut du process
TRACE

  // End
