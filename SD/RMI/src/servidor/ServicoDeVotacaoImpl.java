package servidor;

import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Map;

public class ServicoDeVotacaoImpl extends UnicastRemoteObject implements ServicoDeVotacao{
    private Map<String, String> votos;

    public ServicoDeVotacaoImpl() throws RemoteException {
        super();
        votos = new HashMap<>();
    }

    @Override
    public void votar(String eleitor, String candidato) throws RemoteException {
        if (votos.containsKey(eleitor)) {
            System.out.println(eleitor + " ja votou.");
        } else {
            votos.put(eleitor, candidato);
            System.out.println("Voto registrado para " + candidato);
        }
    }

    @Override
    public Map<String, String> getVotos() throws RemoteException {
        return votos;
    }
}
