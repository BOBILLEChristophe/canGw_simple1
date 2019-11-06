# canGw_simple1


canGw_simple1 est un projet très simple pour scanner les trames circulant sur un bus CAN pour être utilisées par des applications basées elle sur de réseaux TCP.

Il est constitué de :

1 - Une passerelle (ESP32) équipée d’une carte CAN (SN65HVD230) qui lit les trames d’un bus CAN auquel elle est raccordée.

2 – Une application en C/C++  (ici 4D pour la rapidité du prototypage) qui se connecte à la passerelle, reçoit chaque trame dans un buffer et peut ensuite traiter les trames. A noter que le process de scan est autonome par rapport au process qui l’a appelé et qu’il n’est donc pas de ce fait bloquant pour le process appelant qui contribue dans l’exemple présenté au traitement des données. Le process appelé peut-être avorté par le process appelant (ou tout autre process) en changeant la valeur de la variable globale <>quitScan1 de false à true.
