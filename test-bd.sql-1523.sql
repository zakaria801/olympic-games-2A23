alter table athlétes add foreign key (Type_evenement) references evenement (Type_evenement);  
alter table evenement add foreign key (IP_adresse) references Pays (IP_adresse);
creat table guider(
foreign key  (num_cin) re