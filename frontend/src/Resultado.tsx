import { useApp } from './AppContext';
import { useState, useEffect } from 'react';

const taxaDeCompressao = (comprimida: string, original: string) => {
    const diferenca = original.length - comprimida.length;
    return diferenca / original.length;
}

export default function Resultado() {
    const { comprimida, originalString } = useApp();
    const [dicionario, setDicionario] = useState<String | null>();
    const [binario, setBinario] = useState<String | null>();
    const [taxa, setTaxa] = useState<number>(0);

    useEffect(() => {
        setTaxa(taxaDeCompressao(comprimida, originalString))
        const idx = comprimida.indexOf("|");
        if (idx !== -1) {
            setDicionario(comprimida.slice(0, idx));
            setBinario(comprimida.slice(idx + 1));
        } else {
            setDicionario("");
            setBinario(comprimida);
        }
    }, [comprimida]);

    if (!comprimida) return null;

    const dictEntries = dicionario ? dicionario.split(',') : [];

    return (
        <><div className="stats-container">
            <div className="stat-box">
                <span className="stat-label">taxa de compressão</span>
                <span className="stat-value accent">{(taxa * 100).toFixed(2)}%</span>
            </div>
            <div className="stat-box">
                <span className="stat-label">tamanho original</span>
                <span className="stat-value">{originalString && typeof originalString === 'string' ? originalString.length : 0}</span>
            </div>
            <div className="stat-box">
                <span className="stat-label">tamanho comprimido</span>
                <span className="stat-value">{binario ? binario.length : 0}</span>
            </div>
        </div>
            <div className="compressa-container">
                <div className="dictionary">
                    {dictEntries.map((entry, index) => (
                        <div key={index} className="dict-entry">
                            {entry}
                        </div>
                    ))}
                </div>
                <div className="compressed-string">
                    {binario}
                </div>
            </div>
        </>
    );
}