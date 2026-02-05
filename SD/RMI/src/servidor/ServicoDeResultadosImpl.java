package servidor;

import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Map;

public class ServicoDeResultadosImpl extends UnicastRemoteObject implements ServicoDeResultados{
    private ServicoDeVotacao servicoDeVotacao;

    public ServicoDeResultadosImpl(ServicoDeVotacao servicoDeVotacao) throws RemoteException {
        super();
        this.servicoDeVotacao = servicoDeVotacao;
    }

    @Override
    public Map<String, Integer> getResultados() throws RemoteException {
        Map<String, String> votos = servicoDeVotacao.getVotos();

        Map<String, Integer> resultados = new HashMap<>();

        for (String candidato : votos.values()) {
            resultados.put(candidato, resultados.getOrDefault(candidato, 0) + 1);
        }

        return resultados;
    }
}
