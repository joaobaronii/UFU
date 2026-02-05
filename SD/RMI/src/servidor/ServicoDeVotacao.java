package servidor;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;

public interface ServicoDeVotacao extends Remote{
    void votar(String eleitor, String candidato) throws RemoteException;

    Map<String, String> getVotos() throws RemoteException;
}
