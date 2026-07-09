import { useApp } from './AppContext';
import { useState, useEffect } from 'react';

const taxaDeCompressao = (comprimida, original) => {
    const diferenca = original.length() - comprimida.length();
    return diferenca / original.length();
}

export default function Resultado() {
    const { comprimida, original } = useApp();
    const [dicionario, setDicionario] = useState("");
    const [string, setString] = useState("");

    useEffect(() => {
        if (comprimida) {
            const idx = comprimida.indexOf("|");
            if (idx !== -1) {
                setDicionario(comprimida.slice(0, idx));
                setString(comprimida.slice(idx + 1));
            } else {
                setDicionario("");
                setString(comprimida);
            }
        } else {
            setDicionario("");
            setString("");
        }
    }, [comprimida]);

    if (!comprimida) return null;

    const dictEntries = dicionario ? dicionario.split(',') : [];

    return (
        <div className="compressa-container">
            <div className="dictionary">
                {dictEntries.map((entry, index) => (
                    <div key={index} className="dict-entry">
                        {entry}
                    </div>
                ))}
            </div>
            <div className="compressed-string">
                {string}
            </div>
        </div>
    );
}